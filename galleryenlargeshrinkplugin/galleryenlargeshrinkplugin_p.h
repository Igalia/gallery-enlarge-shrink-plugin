/*
 * galleryenlargeshrinkplugin_p.h
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

#ifndef GALLERYENLARGESHRINKPLUGIN_P_H
#define GALLERYENLARGESHRINKPLUGIN_P_H

#include <QPoint>

class GalleryEnlargeShrinkPluginPrivate
{
public:
    //! GalleryEnlargeShrinkPluginPrivate constructor
    GalleryEnlargeShrinkPluginPrivate();

    //! GalleryEnlargeShrinkPluginPrivate destructor
    virtual ~GalleryEnlargeShrinkPluginPrivate();

    //! Focus position
    QPoint m_focusPosition;

    //! If the effect can be applied to the image or not
    bool m_validImage;
};

#endif /* GALLERYENLARGESHRINKPLUGIN_P_H */
