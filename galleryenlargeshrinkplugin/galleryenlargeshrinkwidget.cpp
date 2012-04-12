/*
 * galleryenlargeshrinkwidget.cpp
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

#include "galleryenlargeshrinkwidget.h"
#include "galleryenlargeshrinkwidget_p.h"
#include "galleryenlargeshrinkaboutwidget.h"

#include <MApplication>
#include <MWidgetCreator>
#include <MLocale>
#include <MLayout>
#include <MGridLayoutPolicy>
#include <MLabel>
#include <MButton>
#include <MSlider>
#include <MSeparator>

M_REGISTER_WIDGET_NO_CREATE(GalleryEnlargeShrinkWidget)

GalleryEnlargeShrinkWidgetPrivate::GalleryEnlargeShrinkWidgetPrivate():
    m_shrinkButton(0),
    m_shrinkLabel(0),
    m_radiusSlider(0),
    m_radiusLabel(0),
    m_landscapePolicy(0),
    m_portraitPolicy(0),
    m_aboutSeparator(new MSeparator),
    m_aboutWidget(new GalleryEnlargeShrinkAboutWidget)
{
}

GalleryEnlargeShrinkWidgetPrivate::~GalleryEnlargeShrinkWidgetPrivate()
{
    delete m_shrinkButton;
    delete m_shrinkLabel;
    delete m_radiusSlider;
    delete m_radiusLabel;
    delete m_landscapePolicy;
    delete m_portraitPolicy;
    delete m_aboutSeparator;
    delete m_aboutWidget;
}

GalleryEnlargeShrinkWidget::GalleryEnlargeShrinkWidget(QGraphicsItem* parent) :
    MWidgetController(parent),
    d_ptr(new GalleryEnlargeShrinkWidgetPrivate)
{
    setObjectName("GalleryEnlargeShrinkWidget");
    setStyleName("EnlargeShrinkEditorControl");
    setContentsMargins(0, 0, 0, 0);

    Q_D(GalleryEnlargeShrinkWidget);
    d->m_aboutSeparator->setStyleName("CommonHeaderDividerInverted");
    connect(d->m_aboutWidget, SIGNAL(linkActivated(QString)),
            this, SIGNAL(aboutLinkActivated(QString)));

    d->m_shrinkLabel = new MLabel("Shrink");
    d->m_shrinkLabel->setObjectName("GalleryEnlargeShrinkShrinkLabel");
    d->m_shrinkLabel->setStyleName("CommonSingleTitleInverted");
    d->m_shrinkButton = new MButton();
    d->m_shrinkButton->setObjectName("GalleryEnlargeShrinkButton");
    d->m_shrinkButton->setStyleName("CommonSwitchInverted");
    d->m_shrinkButton->setViewType(MButton::switchType);
    d->m_shrinkButton->setCheckable(true);
    d->m_shrinkButton->setChecked(true);

    d->m_radiusLabel = new MLabel("Radius");
    d->m_radiusLabel->setObjectName("GalleryEnlargeShrinkRadiusLabel");
    d->m_radiusLabel->setStyleName("CommonSingleTitleInverted");
    d->m_radiusSlider = new MSlider();
    d->m_radiusSlider->setObjectName("GalleryEnlargeShrinkRadiusSlider");
    d->m_radiusSlider->setStyleName("CommonSliderInverted");
    d->m_radiusSlider->setRange(0, 100);
    d->m_radiusSlider->setValue(50);
    MLocale locale;
    d->m_radiusSlider->setHandleLabel(locale.formatPercent(0));
    connect(d->m_radiusSlider, SIGNAL(valueChanged(int)),
            SLOT(handleRadiusValueChanged(int)));
    connect(d->m_radiusSlider, SIGNAL(sliderPressed()),
            SLOT(showRadiusSliderHandleLabel()));
    connect(d->m_radiusSlider, SIGNAL(sliderReleased()),
            SLOT(hideRadiusSliderHandleLabel()));


    MLayout* mainLayout = new MLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setAnimation(0);

    d->m_landscapePolicy = new MGridLayoutPolicy(mainLayout);
    d->m_landscapePolicy->setContentsMargins(0, 0, 0, 0);
    d->m_landscapePolicy->setSpacing(0);
    d->m_landscapePolicy->addItem(d->m_shrinkLabel,    0, 0);
    d->m_landscapePolicy->addItem(d->m_shrinkButton,   0, 1);
    d->m_landscapePolicy->addItem(d->m_radiusLabel,    0, 2);
    d->m_landscapePolicy->addItem(d->m_radiusSlider,   0, 3);
    d->m_landscapePolicy->addItem(d->m_aboutSeparator, 1, 0, 1, 4);
    d->m_landscapePolicy->addItem(d->m_aboutWidget,    2, 0, 1, 4);
    d->m_landscapePolicy->setAlignment(d->m_shrinkLabel,    Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_landscapePolicy->setAlignment(d->m_shrinkButton,   Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_landscapePolicy->setAlignment(d->m_radiusLabel,    Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_landscapePolicy->setAlignment(d->m_radiusSlider,   Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_landscapePolicy->setAlignment(d->m_aboutSeparator, Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_landscapePolicy->setAlignment(d->m_aboutWidget,    Qt::AlignVCenter | Qt::AlignHCenter);
    mainLayout->setLandscapePolicy(d->m_landscapePolicy);

    d->m_portraitPolicy = new MGridLayoutPolicy(mainLayout);
    d->m_portraitPolicy->setContentsMargins(0, 0, 0, 0);
    d->m_portraitPolicy->setSpacing(0);
    d->m_portraitPolicy->addItem(d->m_shrinkLabel,    0, 0);
    d->m_portraitPolicy->addItem(d->m_shrinkButton,   0, 1);
    d->m_portraitPolicy->addItem(d->m_radiusLabel,    1, 0);
    d->m_portraitPolicy->addItem(d->m_radiusSlider,   1, 1);
    d->m_portraitPolicy->addItem(d->m_aboutSeparator, 2, 0, 1, 2);
    d->m_portraitPolicy->addItem(d->m_aboutWidget,    3, 0, 1, 2);
    d->m_portraitPolicy->setAlignment(d->m_shrinkLabel,    Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_portraitPolicy->setAlignment(d->m_shrinkButton,   Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_portraitPolicy->setAlignment(d->m_radiusLabel,    Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_portraitPolicy->setAlignment(d->m_radiusSlider,   Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_portraitPolicy->setAlignment(d->m_aboutSeparator, Qt::AlignVCenter | Qt::AlignHCenter);
    d->m_portraitPolicy->setAlignment(d->m_aboutWidget,    Qt::AlignVCenter | Qt::AlignHCenter);
    mainLayout->setPortraitPolicy(d->m_portraitPolicy);

    setLayout(mainLayout);

    // Make sure initial policy is correct
    if (MApplication::activeWindow()) {
        if (MApplication::activeWindow()->orientation() == M::Portrait) {
            d->m_portraitPolicy->activate();
        } else {
            d->m_landscapePolicy->activate();
        }
    } else {
        d->m_landscapePolicy->activate();
    }
}

GalleryEnlargeShrinkWidget::~GalleryEnlargeShrinkWidget()
{
    delete d_ptr;
    d_ptr = 0;
}

int GalleryEnlargeShrinkWidget::radius() const
{
    Q_D(const GalleryEnlargeShrinkWidget);
    return d->m_radiusSlider->value();
}

bool GalleryEnlargeShrinkWidget::shrink() const
{
    Q_D(const GalleryEnlargeShrinkWidget);
    return d->m_shrinkButton->isChecked();
}

bool GalleryEnlargeShrinkWidget::isRadiusSliderHandleLabelVisible() const
{
    Q_D(const GalleryEnlargeShrinkWidget);
    return d->m_radiusSlider->isHandleLabelVisible();
}

void GalleryEnlargeShrinkWidget::showRadiusSliderHandleLabel()
{
    Q_D(GalleryEnlargeShrinkWidget);
    d->m_radiusSlider->setHandleLabelVisible(true);
}

void GalleryEnlargeShrinkWidget::hideRadiusSliderHandleLabel()
{
    Q_D(GalleryEnlargeShrinkWidget);
    d->m_radiusSlider->setHandleLabelVisible(false);
}

void GalleryEnlargeShrinkWidget::handleRadiusValueChanged(int newValue)
{
    if (isRadiusSliderHandleLabelVisible()) {
        MLocale locale;
        QString value(locale.formatPercent(newValue/100.0f));
        Q_D(GalleryEnlargeShrinkWidget);
        d->m_radiusSlider->setHandleLabel(value);
    }
}

void GalleryEnlargeShrinkWidget::enableInput(bool enabled)
{
    // Don't disable the complete widget as we still want to react to
    // device orientation changes and click in the About widget links.
    Q_D(GalleryEnlargeShrinkWidget);
    d->m_shrinkButton->setEnabled(enabled);
    d->m_shrinkLabel->setEnabled(enabled);
    d->m_radiusSlider->setEnabled(enabled);
    d->m_radiusLabel->setEnabled(enabled);
}
