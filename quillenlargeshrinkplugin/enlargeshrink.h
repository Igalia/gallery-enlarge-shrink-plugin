/*
 * enlargeshrinkplugin.h
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

#ifndef ENLARGESHRINK_H
#define ENLARGESHRINK_H

#include <QuillImageFilterImplementation>

/*!
  \class EnlargeShrink

  \brief Applies an "enlarge" or "shrink" effect to an image, also known as
  "punch" or "pinch" effects respectively.

  Domain based name: com.igalia.enlargeshrink

  Options supported:
  Radius (radius of the area affected by the effect),
  Center (coordinates of the center of the area affected by the effect),
  Force (force of the effect to be applied).
*/
class EnlargeShrink:
    public QuillImageFilterImplementation
{
public:
    //! EnlargeShrink constructor
    EnlargeShrink();

    //! EnlargeShrink destructor
    ~EnlargeShrink();

    //! \reimp
    QuillImage apply(const QuillImage& image) const;

    //! \reimp
    virtual const QString name() const;

    //! \reimp
    const QStringList supportedOptions() const;

    //! \reimp
    bool setOption(const QString &option, const QVariant &value);

    //! \reimp
    QVariant option(const QString &option) const;

private:
    //! Applies the enlarge/shrink effect over the image
    bool enlargeShrink(const QuillImage &img, QuillImage *outputImg) const;

    double getRadius(const QuillImage &img) const;

    QPoint getCenter(const QuillImage &img) const;

    //! Radius of the area where the effect is applied (in pixels)
    double m_Radius;

    //! Center of the area where the effect is applied
    QPoint m_Center;

    //! Force of the effect. Allowed values are in the interval [-1.0 .. 1.0]
    //! Negative values cause an shrink effect  (also known as "pinch")
    //! Positive values cause an enlarge effect (also known as "punch")
    //! Zero causes no effect
    double m_Force;
};

#endif /* ENLARGESHRINK_H */
