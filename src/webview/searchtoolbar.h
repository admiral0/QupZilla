/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2011  David Rosca
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
* ============================================================ */
#ifndef SEARCHTOOLBAR_H
#define SEARCHTOOLBAR_H

#include <QLineEdit>
#include <QToolButton>
#include <QWebPage>
#include <QLabel>
#include <QFlags>
#include <QPropertyAnimation>
#include "animatedwidget.h"

namespace Ui
{
class SearchToolbar;
}

class QupZilla;
class LineEdit;
class SearchToolBar : public AnimatedWidget
{
    Q_OBJECT
public:
    explicit SearchToolBar(QupZilla* mainClass, QWidget* parent = 0);
    ~SearchToolBar();

    QLineEdit* searchLine();
    bool eventFilter(QObject* obj, QEvent* event);

signals:

public slots:
    void searchText(const QString &text);
    void refreshFindFlags();
    void findNext();
    void findPrevious();

private:
    Ui::SearchToolbar* ui;
    QupZilla* p_QupZilla;

    QPropertyAnimation* m_animation;
    int m_findFlags;
};

#endif // SEARCHTOOLBAR_H
