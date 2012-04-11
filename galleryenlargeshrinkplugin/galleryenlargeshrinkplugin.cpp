/*
 * galleryenlargeshrinkplugin.cpp
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

#include "galleryenlargeshrinkplugin.h"
#include "galleryenlargeshrinkplugin_p.h"
#include "galleryenlargeshrinkwidget.h"

#include <galleryedituiprovider.h>
#include <MLibrary>
#include <MApplication>
#include <MBanner>
#include <MMessageBox>
#include <MLabel>
#include <QGraphicsSceneMouseEvent>
#include <QuillImageFilter>


static const float   EFFECT_FORCE          = 1.0;
static const int     TAP_DISTANCE          = 20;
static const int     PORTRAIT_HEIGHT       = 120;
static const int     LANDSCAPE_HEIGHT      = 72;
static const int     INFOBANNER_TIMEOUT    = 2 * 1000;
static const int     IMAGE_MAX_HEIGHT      = 512;
static const int     IMAGE_MAX_WIDTH       = 512;

M_LIBRARY

GalleryEnlargeShrinkPluginPrivate::GalleryEnlargeShrinkPluginPrivate() :
    m_focusPosition(),
    m_validImage(true)
{
}

GalleryEnlargeShrinkPluginPrivate::~GalleryEnlargeShrinkPluginPrivate()
{
}

GalleryEnlargeShrinkPlugin::GalleryEnlargeShrinkPlugin(QObject* parent) :
    GalleryEditPlugin(parent),
    d_ptr(new GalleryEnlargeShrinkPluginPrivate())
{
}


GalleryEnlargeShrinkPlugin::~GalleryEnlargeShrinkPlugin()
{
    delete d_ptr;
}

QString GalleryEnlargeShrinkPlugin::name() const
{
    return QString("Enlarge - Shrink");
}


QString GalleryEnlargeShrinkPlugin::iconID() const
{
    return QString("icon-m-image-edit-enlarge-shrink");
}

bool GalleryEnlargeShrinkPlugin::containsUi() const
{
    return true;
}

bool GalleryEnlargeShrinkPlugin::zoomingAllowed() const
{
    return true;
}

QGraphicsWidget* GalleryEnlargeShrinkPlugin::createToolBarWidget(QGraphicsItem* parent)
{
    GalleryEnlargeShrinkWidget* widget = new GalleryEnlargeShrinkWidget(parent);
    return widget;
}

const QSize GalleryEnlargeShrinkPlugin::toolBarWidgetSize(const M::Orientation& orientation) const
{
    QSize size = GalleryEditPlugin::toolBarWidgetSize(orientation);

    if (M::Portrait == orientation) {
        size.setHeight(PORTRAIT_HEIGHT);
    } else {
        size.setHeight(LANDSCAPE_HEIGHT);
    }

    return size;
}

bool GalleryEnlargeShrinkPlugin::receiveMouseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event &&
        event->type() == QEvent::GraphicsSceneMouseRelease &&
        event->button() == Qt::LeftButton &&
        (event->scenePos() - event->buttonDownScenePos(Qt::LeftButton)).manhattanLength() < TAP_DISTANCE) {
        Q_D(GalleryEnlargeShrinkPlugin);
        if (d->m_validImage) {
            d->m_focusPosition = event->pos().toPoint();
            performEditOperation();
            return true;
        } else {
            showInfoBanner("Plugin disabled for this image size");
        }
    }
    return false;
}

void GalleryEnlargeShrinkPlugin::activate()
{
    if (editUiProvider()) {
        Q_D(GalleryEnlargeShrinkPlugin);
        d->m_validImage = editUiProvider()->fullImageSize().height() <= IMAGE_MAX_HEIGHT &&
                          editUiProvider()->fullImageSize().width()  <= IMAGE_MAX_WIDTH;
        if (d->m_validImage) {
            showInfoBanner("Tap on an area to keep it focused");
        } else {
            showMessageBox("Enlarge Shrink plugin limitations",
                           "Gallery Enlarge Shrink plugin is currently limited to "
                           "small images (512x512)<br />"
                           "For a given image:"
                           "<ol>"
                           "<li>Scale it or crop it</li>"
                           "<li>Save it with a different name</li>"
                           "<li>Apply the filter to the new one</li>"
                           "</ol>");
            GalleryEnlargeShrinkWidget* widget = static_cast<GalleryEnlargeShrinkWidget*>(toolBarWidget());
            widget->setEnabled(d->m_validImage);
        }
    }
}

void GalleryEnlargeShrinkPlugin::performEditOperation()
{
    if (editUiProvider()) {
        Q_D(GalleryEnlargeShrinkPlugin);
        QHash<QuillImageFilter::QuillFilterOption, QVariant> optionHash;
        const QPoint imagePosition = editUiProvider()->convertScreenCoordToImageCoord(d->m_focusPosition);
        if (imagePosition != QPoint(-1, -1)) {
            GalleryEnlargeShrinkWidget* widget = static_cast<GalleryEnlargeShrinkWidget*>(toolBarWidget());
            optionHash.insert(QuillImageFilter::Center, QVariant(imagePosition));
            double radius = widget->radius() / 100.0 * qMin(editUiProvider()->fullImageSize().width(),
                                                            editUiProvider()->fullImageSize().height());
            optionHash.insert(QuillImageFilter::Radius, radius);
            // To enlarge (punch effect) "force" must be positive
            // To shrink  (pinch effect) "force" must be negative
            optionHash.insert("force", EFFECT_FORCE * (widget->shrink()? -1 : 1));
            editUiProvider()->runEditFilter("com.igalia.enlargeshrink", optionHash);
            emit editOperationPerformed();
        }
    }
}

MMessageBox* GalleryEnlargeShrinkPlugin::showMessageBox(const QString& title, const QString& text) const
{
    MMessageBox* messageBox = new MMessageBox(title, "");
    MLabel* innerLabel = new MLabel(messageBox);
    innerLabel->setWordWrap(true);
    innerLabel->setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
    innerLabel->setStyleName("CommonQueryText");
    innerLabel->setText(text);
    innerLabel->setAlignment(Qt::AlignHCenter);
    messageBox->setCentralWidget(innerLabel);
    connect(this, SIGNAL(deactivated()),
            messageBox, SLOT(disappear()));
    messageBox->appear(MSceneWindow::DestroyWhenDone);

    return messageBox;
}

MBanner* GalleryEnlargeShrinkPlugin::showInfoBanner(const QString& title) const
{
    MBanner *infoBanner = new MBanner;
    infoBanner->setStyleName("InformationBanner");
    infoBanner->setTitle(title);
    infoBanner->model()->setDisappearTimeout(INFOBANNER_TIMEOUT);
    connect(this, SIGNAL(deactivated()),
            infoBanner, SLOT(disappear()));
    infoBanner->appear(MApplication::activeWindow(), MSceneWindow::DestroyWhenDone);

    return infoBanner;
}

Q_EXPORT_PLUGIN2(galleryenlargeshrinkplugin, GalleryEnlargeShrinkPlugin)
