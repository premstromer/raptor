/* This file is part of the KDE project

   Copyright (C) 2008 Alessandro Diaferia <alediaferia@gmail.com>

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
*/

#ifndef RAPTORGRAPHICSWIDGET_H
#define RAPTORGRAPHICSWIDGET_H

#include <QGraphicsWidget>
#include <plasma/querymatch.h>

class KUrl;

class RaptorGraphicsWidget : public QGraphicsWidget
{
    Q_OBJECT
    public:
        RaptorGraphicsWidget(QGraphicsItem *parent);
        ~RaptorGraphicsWidget();

    protected:
//         QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint = QSizeF() ) const;
        void resizeEvent(QGraphicsSceneResizeEvent *event);

    protected slots:
        void updateColors();
        void launchApplication(const KUrl &);
        void scrollLeft();
        void scrollRight();
        void refineModel();
        void matchesChanged(const QList<Plasma::QueryMatch>&);

    private:
        class Private;
        Private *d;

};

#endif
