/*
 * galleryenlargeshrinkwidget.h
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

#ifndef GALLERYENLARGESHRINKWIDGET_H
#define GALLERYENLARGESHRINKWIDGET_H

#include <MWidgetController>

class GalleryEnlargeShrinkWidgetPrivate;

class GalleryEnlargeShrinkWidget : public MWidgetController
{
    Q_OBJECT
public:
    //! GalleryEnlargeShrinkWidget constructor
    //! \param parent Optional parent
    GalleryEnlargeShrinkWidget(QGraphicsItem* parent = 0);

    //! GalleryEnlargeShrinkWidget destructor
    virtual ~GalleryEnlargeShrinkWidget();

    //! Get function for the radius slider value
    //! \return Selected radius value
    int radius() const;

    //! Get function for the shrink/enlarge button value
    //! \return True if the shrink button is checked, false otherwise
    bool shrink() const;

    //! Get function for the radius slider handle visibility
    //! \return True if visible, otherwise false
    bool isRadiusSliderHandleLabelVisible() const;

public Q_SLOTS:
    //! Called to show the radius slider handle label
    void showRadiusSliderHandleLabel();

    //! Called to hide the radius slider handle label
    void hideRadiusSliderHandleLabel();

    //! Updates the radius slider handle label to the current value
    void handleRadiusValueChanged(int newValue);

private:
    Q_DISABLE_COPY(GalleryEnlargeShrinkWidget)
    Q_DECLARE_PRIVATE(GalleryEnlargeShrinkWidget)
    GalleryEnlargeShrinkWidgetPrivate* d_ptr;
};

#endif /* GALLERYENLARGESHRINKWIDGET_H */
