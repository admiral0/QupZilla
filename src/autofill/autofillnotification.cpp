/* ============================================================
* QupZilla - WebKit based browser
* Copyright (C) 2010-2011  nowrep
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
#include "autofillnotification.h"
#include "ui_autofillnotification.h"
#include "autofillmodel.h"
#include "mainapplication.h"

AutoFillNotification::AutoFillNotification(QUrl url, QByteArray data, QString pass, QWidget *parent)
   :QWidget(parent)
   ,ui(new Ui::AutoFillWidget)
   ,m_url(url)
   ,m_data(data)
   ,m_pass(pass)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    ui->label->setText(tr("Do you want QupZilla to remember password on %1?").arg(url.host()));
    ui->closeButton->setIcon(
#ifdef Q_WS_X11
    style()->standardIcon(QStyle::SP_DialogCloseButton)
#else
    QIcon(":/icons/faenza/close.png")
#endif
    );

    connect(ui->remember, SIGNAL(clicked()), this, SLOT(remember()));
    connect(ui->never, SIGNAL(clicked()), this, SLOT(never()));
    connect(ui->notnow, SIGNAL(clicked()), this, SLOT(hide()));
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(hide()));

    m_animation = new QTimeLine(300, this);
    m_animation->setFrameRange(0, sizeHint().height());

    setMinimumHeight(1);
    setMaximumHeight(1);
    connect(m_animation, SIGNAL(frameChanged(int)),this, SLOT(frameChanged(int)));
    QTimer::singleShot(1, m_animation, SLOT(start()));
}

void AutoFillNotification::hide()
{
    m_animation->setDirection(QTimeLine::Backward);

    m_animation->stop();
    m_animation->start();
    connect(m_animation, SIGNAL(finished()), this, SLOT(close()));
}

void AutoFillNotification::frameChanged(int frame)
{
    setMinimumHeight(frame);
    setMaximumHeight(frame);
}

void AutoFillNotification::never()
{
    MainApplication::getInstance()->autoFill()->blockStoringfor(m_url);
    hide();
}

void AutoFillNotification::remember()
{
    MainApplication::getInstance()->autoFill()->addEntry(m_url, m_data, m_pass);
    hide();
}

AutoFillNotification::~AutoFillNotification()
{
    delete ui;
}