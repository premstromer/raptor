/* This file is part of the KDE project

   Copyright (C) 2008 Lukas Appelhans <l.appelhans@gmx.de>
   Copyright (C) 2008 Dario Freddi <drf54321@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/
#include "raptorbreadcrumbitem.h"

#include <QPainter>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QTimeLine>
#include <QEvent>

#include <KIcon>
#include <KDebug>

class RaptorBreadCrumbItem::Private
{
public:
    Private(RaptorBreadCrumbItem *q) 
      : q(q),
        timeLine(0),
        frame(0)
    {
        timeLine = new QTimeLine(250, q);
    }

    RaptorBreadCrumbItem *q;
    QModelIndex index;
    QTimeLine * timeLine;
    int frame;
    QColor textColor;
};

RaptorBreadCrumbItem::RaptorBreadCrumbItem(const QIcon & icon, const QString & text,
                                           const QModelIndex &index, QWidget * parent)
  : QPushButton(icon, text, parent),
    d(new Private(this))
{
    setAttribute(Qt::WA_NoSystemBackground);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setMaximumSize(QSize(22, 22));

    d->index = index;

    installEventFilter(this);

    connect(this, SIGNAL(clicked()), SLOT(emitNavigationRequested()));
    connect(d->timeLine, SIGNAL(frameChanged(int)), SLOT(animatePaint(int)));
}

RaptorBreadCrumbItem::~RaptorBreadCrumbItem()
{
    delete d;
}

void RaptorBreadCrumbItem::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    
    QPainter p(this);
    if (d->frame) {
        setMaximumSize(QSize(22 + d->frame, 22));
        p.setPen(d->textColor);
        p.drawText(contentsRect(), text());
    }
    p.drawPixmap(contentsRect(), icon().pixmap(22, 22));
}

const QModelIndex RaptorBreadCrumbItem::index()
{
    return d->index;
}

void RaptorBreadCrumbItem::emitNavigationRequested()
{
    emit navigationRequested(index(), this);
}

bool RaptorBreadCrumbItem::eventFilter(QObject * watched, QEvent * event)
{
    Q_UNUSED(watched)
    switch(event->type())
    {
        case QEvent::HoverEnter:
            d->timeLine->setFrameRange(0, 20);
            d->timeLine->start();
            return false;
        case QEvent::HoverLeave:
            d->timeLine->stop();
            d->frame = 0;
            repaint();
            return false;
        default:
            return false;
    };
}

void RaptorBreadCrumbItem::animatePaint(int frame)
{
    d->frame = frame;
    repaint();
}

void RaptorBreadCrumbItem::setTextColor(const QColor &color)
{
    d->textColor = color;
}

class RaptorBreadCrumbArrow::Private
{
    public:
        Private(QAbstractItemModel * m)
          : model(m)
        {}
        ~Private() {}

        QAbstractItemModel * model;
};

RaptorBreadCrumbArrow::RaptorBreadCrumbArrow(const QModelIndex &index, QAbstractItemModel * model, QWidget * parent)
  : RaptorBreadCrumbItem(KIcon("arrow-right"), QString(), index, parent),
    d(new Private(model))
{
    disconnect(SIGNAL(clicked()), this, SLOT(emitNavigationRequested()));
}

RaptorBreadCrumbArrow::~RaptorBreadCrumbArrow()
{
    delete d;
}

void RaptorBreadCrumbArrow::paintEvent(QPaintEvent * event)
{
    Q_UNUSED(event);
    
    QPainter p(this);
    p.drawPixmap(contentsRect(), icon().pixmap(22, 22));
}

#include "raptorbreadcrumbitem.moc"
