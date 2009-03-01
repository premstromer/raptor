/* This file is part of the KDE project

   Copyright (C) 2008 Alessandro Diaferia <alediaferia@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#include "breadcrumb.h"
#include "breadcrumbitem.h"

#include <QRectF>

Breadcrumb::Breadcrumb(QAbstractItemModel *model, QGraphicsWidget *parent) : QGraphicsWidget(parent), m_model(model)
{
}

Breadcrumb::~Breadcrumb()
{}

void Breadcrumb::setCurrentItem(const QModelIndex &index)
{
    // maybe this is a bit drastic
    qDeleteAll(m_items);
    m_items.clear();

    m_items << new BreadcrumbItem; // the arrow
    BreadcrumbItem *mainMenu = new BreadcrumbItem;
    mainMenu->setIsMainMenu(true);
    m_items << mainMenu;

    if (!index.isValid()) { // we always set the main menu as first element
        return;
    }

    QModelIndex currentIndex = index;

    qreal x = 0;
    do {
        m_items << new BreadcrumbItem; // the arrow
        BreadcrumbItem *item = new BreadcrumbItem(currentIndex);
        item->setRect(QRectF(x, 0, height(), height()));
        m_items << item;

        x += height();
        currentIndex = m_model->parent(currentIndex);
    } while (currentIndex.isValid())
}
