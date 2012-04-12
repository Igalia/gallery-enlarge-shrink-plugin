/*
 * galleryenlargeshrinkplugin.h
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

#ifndef GALLERYENLARGESHRINKPLUGIN_H
#define GALLERYENLARGESHRINKPLUGIN_H

#include <galleryeditplugin.h>

class MBanner;
class MMessageBox;
class GalleryEnlargeShrinkPluginPrivate;

class GalleryEnlargeShrinkPlugin: public GalleryEditPlugin
{
    Q_OBJECT
    Q_INTERFACES(GalleryEditPlugin);

public:
    //! GalleryEnlargeShrinkPlugin constructor
    //! \param parent Optional parent
    GalleryEnlargeShrinkPlugin(QObject* parent = 0);

    //! GalleryEnlargeShrink destructor
    virtual ~GalleryEnlargeShrinkPlugin();

    //! \reimp
    QString name() const;

    //! \reimp
    QString iconID() const;

    //! \reimp
    bool containsUi() const;

    //! \reimp
    bool zoomingAllowed() const;

    //! \reimp
    bool receiveMouseEvent(QGraphicsSceneMouseEvent *event);

    //! \reimp
    const QSize toolBarWidgetSize(const M::Orientation& orientation) const;

public Q_SLOTS:
    //! \reimp
    void performEditOperation();

    //! \reimp
    void activate();

    //! Shows a message box with a given title and text
    //! \param title Text to be shown as a title in the message box
    //! \param text Text to be shown as the body in the message box
    //! \return The message box
    MMessageBox* showMessageBox(const QString& title, const QString& text) const;

    //! Shows an info banner with a given text
    //! \param title Text to be shown in the info banner
    //! \return The info banner
    MBanner* showInfoBanner(const QString& text) const;

    //! Invoked when a link in the about notice has been activated
    //! \param link The activated link
    void onAboutLinkActivated(const QString& link);

protected:
    //! \reimp
    QGraphicsWidget* createToolBarWidget(QGraphicsItem* parent = 0);

private:
    Q_DISABLE_COPY(GalleryEnlargeShrinkPlugin)
    Q_DECLARE_PRIVATE(GalleryEnlargeShrinkPlugin)
    GalleryEnlargeShrinkPluginPrivate* d_ptr;
};

#endif /* GALLERYENLARGESHRINKPLUGIN_H */
