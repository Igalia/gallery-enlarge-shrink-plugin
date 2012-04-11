/*
 * quillenlargeshrinkplugin.h
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

#ifndef QUILLENLARGESHRINKPLUGIN_H
#define QUILLENLARGESHRINKPLUGIN_H

#include <QuillImageFilterInterface>
#include <QuillImageFilterImplementation>

class QuillEnlargeShrinkPlugin:
    public QObject,
    public QuillImageFilterInterface
{
    Q_OBJECT
    Q_INTERFACES(QuillImageFilterInterface)

public:
    //! QuillEnlargeShrinkPlugin constructor
    QuillEnlargeShrinkPlugin();

    //! \reimp
    QuillImageFilterImplementation* create(const QString& name);

    //! \reimp
    const QStringList name() const;

private:
    Q_DISABLE_COPY(QuillEnlargeShrinkPlugin)
};

#endif /* QUILLENLARGESHRINKPLUGIN_H */
