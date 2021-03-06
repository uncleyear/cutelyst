/*
 * Copyright (C) 2013-2015 Daniel Nicoletti <dantti12@gmail.com>
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

#ifndef VIEW_H
#define VIEW_H

#include <QObject>

#include <Cutelyst/cutelyst_global.h>
#include <Cutelyst/component.h>

namespace Cutelyst {

class Context;

/*! \class View view.h Cutelyst/View
 * @brief %Cutelyst %View abstract view component
 */
class CUTELYST_LIBRARY View : public Component
{
    Q_OBJECT
public:
    /**
     * The base implementation for a View class, a name
     * for the view should be set to be found by Context->view()
     */
    explicit View(QObject *parent, const QString &name = QString());
    virtual ~View();

    /**
     * Returns the name of the view
     */
    // TODO remove Cutelyst2
    QString name() const;

    /**
     * The default implementation returns Component::OnlyExecute
     */
    virtual Modifiers modifiers() const override;

    /**
     * All subclasses must reimplement this when doing it's rendering.
     * If an error (c->error()) is not set c->response()->body() is defined
     * with the returned value, this is useful if the view is not
     * meant to be used as a body.
     */
    virtual QByteArray render(Context *c) const = 0;

private:
    /**
     * This is used by Component execute() when
     * using an ActionView
     */
    bool doExecute(Context *c) final;
};

}

#endif // VIEW_H
