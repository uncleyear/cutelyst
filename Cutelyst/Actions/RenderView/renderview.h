/*
 * Copyright (C) 2014-2016 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include <Cutelyst/cutelyst_global.h>
#include <Cutelyst/action.h>
#include <Cutelyst/componentfactory.h>

namespace Cutelyst {

class RenderViewPrivate;
class CUTELYST_PLUGIN_ACTION_RENDERVIEW_EXPORT RenderView : public Action
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(RenderView)
public:
    /**
     * Constructs a RenderView object with the given \arg parent.
     */
    explicit RenderView(QObject *parent = nullptr);
    virtual ~RenderView();

    /**
     * Reimplemented from Plugin::init()
     */
    virtual bool init(Application *application, const QVariantHash &args) override;

protected:
    virtual bool doExecute(Cutelyst::Context *c) override;

    RenderViewPrivate *d_ptr;
};

class RenderViewFactory : public QObject, public ComponentFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.cutelyst.ComponentFactory" FILE "metadata.json")
    Q_INTERFACES(Cutelyst::ComponentFactory)
public:
    Component *createComponent(QObject *parent) { return new RenderView(parent); }
};

}


#endif // RENDERVIEW_H
