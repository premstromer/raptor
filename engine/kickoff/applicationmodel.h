/*
    Copyright 2007 Pino Toscano <pino@kde.org>
    Copyright 2007 Robert Knight <robertknight@gmail.com>
    Copyright (C) 2008 Dario Freddi <drf54321@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include "kickoffabstractmodel.h"

namespace Kickoff
{

class ApplicationModelPrivate;

/**
 * ApplicationModel provides a tree model containing all of the user's installed graphical programs.
 * The applications are arranged into categories, based on the information in their .desktop files.
 */
class ApplicationModel : public KickoffAbstractModel
{
    Q_OBJECT

    public:
        ApplicationModel(QObject *parent = 0);
        virtual ~ApplicationModel();

        void init();

        /**
         * This enum describes the policy for
         * handling duplicate applications (that is,
         * two applications with the same name in the same group)
         */
        enum DuplicatePolicy
        {
            /** Display duplicate entries. */
            ShowDuplicatesPolicy,
            /**
             * Show only the entry for the most recent
             * version of the application.
             *
             * Currently only a crude heuristic to determine whether the
             * application is from KDE 3 or KDE 4 is used to determine
             * recent-ness.
             *
             * eg.  If MyGame/KDE 3 and MyGame/KDE 4 are found
             * show only MyGame/KDE 4
             */
            ShowLatestOnlyPolicy
        };

        /**
         * Sets the policy for handling duplicate applications.
         * See DuplicatePolicy
         */
        void setDuplicatePolicy(DuplicatePolicy policy);
        /** See setDuplicatePolicy() */
        DuplicatePolicy duplicatePolicy() const;

        // reimplemented from QAbstractItemModel
        virtual bool canFetchMore(const QModelIndex &parent) const;
        virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
        virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
        virtual void fetchMore(const QModelIndex &parent);
        virtual bool hasChildren(const QModelIndex &parent = QModelIndex()) const;
        virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
        virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        virtual QModelIndex parent(const QModelIndex &index) const;
        virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;

    public slots:
        void slotReloadMenu();
        void checkSycocaChange();
        void addAppNode(KService::Ptr entry);
        void clearModelData();

    private:
        friend class ApplicationModelPrivate;
        ApplicationModelPrivate *const d;

        Q_DISABLE_COPY(ApplicationModel)
};

}

#endif
