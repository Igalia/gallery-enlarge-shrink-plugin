/*
 * enlargeshrinkplugin.cpp
 *
 * Copyright (C) 2012 Igalia, S.L.
 * Author: Antia Puentes <apuentes@igalia.com>
 *
 * This file is part of the Gallery Enlarge/Shrink Plugin.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; version 2.1 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see http://www.gnu.org/licenses/ *
 */

#include "enlargeshrink.h"

#include <math.h>

#define FILTER_NAME_ENLARGESHRINK "com.igalia.enlargeshrink"
#define FORCE_OPTION "force"
#define FORCE_FACTOR 3.2

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

// Maximum "width" of a pixel, measured diagonally
#ifndef M_SQRT2
#define M_SQRT2 1.41421356237309504880168872420969808
#endif

#define FIXEDPOINT_FRACTIONBITS 8
#define FIXEDPOINT_MULTIPLIER (1 << FIXEDPOINT_FRACTIONBITS)


static double fraction(double n)
{
    return n - floor(n);
}

static int fixedfraction(double n)
{
    return (int) (fraction(n) * FIXEDPOINT_MULTIPLIER);
}

static QRgb weighpixel(QRgb rgb, int percentage)
{
    return qRgb((qRed(rgb)   * percentage) >> (FIXEDPOINT_FRACTIONBITS * 2),
                (qGreen(rgb) * percentage) >> (FIXEDPOINT_FRACTIONBITS * 2),
                (qBlue(rgb)  * percentage) >> (FIXEDPOINT_FRACTIONBITS * 2));
}

/*
 * Gets a pixel at a floating-point coordinate, thus causing it to take into
 * accountance neighbour pixels if one of the coordinates have a fractional part
 *
 * The function will calculate the pixel value by calculating all areas the
 * pixel occupies in each neighbouring pixel.
 */
static QRgb getPixel(const QImage &img, double x, double y)
{
    int fx = fixedfraction(x);
    int fy = fixedfraction(y);

    int px = (int) x;
    int py = (int) y;

    int right = 1;
    if (px >= img.width() - 1) {
        right = 0;
    }

    int below = 1;
    if (py >= img.height() - 1) {
        below = 0;
    }

    QRgb p1 = weighpixel(img.pixel(px, py), (FIXEDPOINT_MULTIPLIER - fx) * (FIXEDPOINT_MULTIPLIER - fy));
    QRgb p2 = weighpixel(img.pixel(px + right, py), fx * (FIXEDPOINT_MULTIPLIER - fy));
    QRgb p3 = weighpixel(img.pixel(px, py + below), (FIXEDPOINT_MULTIPLIER - fx) * fy);
    QRgb p4 = weighpixel(img.pixel(px + right, py + below), fx * fy);

    return qRgb((qRed(p1) + qRed(p2) + qRed(p3) + qRed(p4)),
                (qGreen(p1) + qGreen(p2) + qGreen(p3) + qGreen(p4)),
                (qBlue(p1) + qBlue(p2) + qBlue(p3) + qBlue(p4)));

}

/**
 * Returns the enlarge/shrink effect for a given "n".
 * The function should be continous and should return 0 for x=0 and return 1 for
 * x = 1 if not, abrupt changes might appear in the image. The function only
 * needs to be valid for the interval [0..1].
 * \a amplitude should be in the interval [-0.3125, 0.3125], if it is outside
 * this interval the function might return negative values (which might give
 * interesting effects but not an enlarge/shrink effect)
 * A positive \a amplitude will give a "punch", negative a "pinch"
 *
 * Keeping the function linear (return x;) will in theory not change the image,
 * but due to rounding errors one might expect minor distortion.
 */
static double distort(double n, double amplitude)
{
    return n - sin(M_PI * n) * amplitude;
}

EnlargeShrink::EnlargeShrink() :
    m_Radius(0), m_Center(-1, -1), m_Force(0)
{
}

EnlargeShrink::~EnlargeShrink()
{
}

const QString EnlargeShrink::name() const
{
    return FILTER_NAME_ENLARGESHRINK;
}

const QStringList EnlargeShrink::supportedOptions() const
{
    QStringList supportedOptions;
    supportedOptions << QuillImageFilter::Radius
                     << QuillImageFilter::Center
                     << FORCE_OPTION;
    return supportedOptions;
}

bool EnlargeShrink::setOption(const QString &option, const QVariant &value)
{
    bool ok = false;

    if (option == QuillImageFilter::Radius) {
        double radius = value.toDouble(&ok);
        if (ok) {
            m_Radius = radius;
        }

    } else if (option == QuillImageFilter::Center) {
        QPoint center = value.toPoint();
        if (!center.isNull()) {
            m_Center = center;
            ok = true;
        }

    } else if (option == FORCE_OPTION) {
        double force = value.toDouble(&ok);
        ok = ok && force <= 1.0 && force >= -1.0;
        if (ok) {
            // Divide by the FORCE_FACTOR to get appropiated values for
            // the Amplitude used by the "distort" function
            m_Force = force/FORCE_FACTOR;
        }
    }

    return ok;
}

QVariant EnlargeShrink::option(const QString &option) const
{
    QVariant value;

    if (option == QuillImageFilter::Radius) {
        value = m_Radius;
    } else if (option == QuillImageFilter::Center) {
        value = m_Center;
    } else if (option == FORCE_OPTION) {
        value = m_Force * FORCE_FACTOR;
    }

    return value;
}

QuillImage EnlargeShrink::apply(const QuillImage& image) const
{
    if (image.fullImageSize().isEmpty()) {
        return QImage();
    }

    QuillImage out;
    enlargeShrink(image, &out);
    return out;
}

double EnlargeShrink::getRadius(const QuillImage &img) const
{
    double radius = m_Radius;
    if (!img.isFragment() || (img.width() == 170 && img.height() == 170)) {
        if (img.fullImageSize().width() < img.fullImageSize().height()) {
            radius = radius * img.width() / img.fullImageSize().width();
        } else {
            radius = radius * img.height() / img.fullImageSize().height();
        }
    }
    return radius;
}

QPoint EnlargeShrink::getCenter(const QuillImage &img) const
{
    QPoint center = m_Center;
    if (!img.isFragment() || (img.width() == 170 && img.height() == 170)) {
        center.setX(center.x() * img.width()  / img.fullImageSize().width());
        center.setY(center.y() * img.height() / img.fullImageSize().height());
    }
    return center;
}

bool EnlargeShrink::enlargeShrink(const QuillImage &img,
                                  QuillImage *outputImg) const
{
    *outputImg = img;

    double radius = getRadius(img);
    QPoint center = getCenter(img);

    for (int y = 0; y < img.height(); y++) {
        for (int x = 0; x < img.width(); x++) {
            int dx = x - center.x();
            int dy = y - center.y();
            double distance = sqrt(dx * dx + dy * dy);
            if (distance <= radius + M_SQRT2) {
                // Evaluate the area inside the radius + this M_SQRT2
                // (to reduce aliasing effects)
                double n = distance / radius;
                if (n > 0.0 && n < 1.0) {
                    n = distort(n, m_Force);
                }
                // Normalize the distance vector< and find the length after
                // distortion
                if (dx != 0 || dy != 0) {
                    double mag = n * radius/distance;
                    dx = dx * mag;
                    dy = dy * mag;
                }
                double tx = center.x() + dx;
                double ty = center.y() + dy;
                // Crop off overflows
                if (tx > img.width()  || tx < 0) tx = x;
                if (ty > img.height() || ty < 0) ty = y;

                outputImg->setPixel(x, y, getPixel(img, tx, ty));
            }
        }
    }

    return true;
}
