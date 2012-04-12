/*
 * galleryenlargeshrinkwidget_p.h
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

#ifndef GALLERYENLARGESHRINKWIDGET_P_H
#define GALLERYENLARGESHRINKWIDGET_P_H

class MGridLayoutPolicy;
class MSlider;
class MButton;
class MLabel;
class MSeparator;
class GalleryEnlargeShrinkAboutWidget;

class GalleryEnlargeShrinkWidgetPrivate
{
public:
    //! GalleryEnlargeShrinkWidgetPrivate constructor
    GalleryEnlargeShrinkWidgetPrivate();

    //! GalleryEnlargeShrinkWidgetPrivate destructor
    virtual ~GalleryEnlargeShrinkWidgetPrivate();

    //! Button to select between "enlarge" or "shrink"
    MButton *m_shrinkButton;

    //! Label associated to the shrink button
    MLabel *m_shrinkLabel;

    //! Slider to choose the focus area radius
    MSlider* m_radiusSlider;

    //! Label associated to the radius slider
    MLabel *m_radiusLabel;

    //! Landscape policy for the focus area layout
    MGridLayoutPolicy* m_landscapePolicy;

    //! Portrait policy for the focus area layout
    MGridLayoutPolicy* m_portraitPolicy;

    //! Separator dividing the widget from the about claim
    MSeparator* m_aboutSeparator;

    //! Widget containing the about disclaimer
    GalleryEnlargeShrinkAboutWidget* m_aboutWidget;
};

#endif /* GALLERYENLARGESHRINKWIDGET_P_H */
