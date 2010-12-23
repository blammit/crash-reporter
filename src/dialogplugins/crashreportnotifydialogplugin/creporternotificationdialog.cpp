/*
 * This file is part of crash-reporter
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Ville Ilvonen <ville.p.ilvonen@nokia.com>
 * Author: Riku Halonen <riku.halonen@nokia.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

// System includes.

#include <QSignalMapper>
#include <QGraphicsGridLayout>

#include <MTextEdit>
#include <MButton>
#include <MLabel>
#include <MLayout>
#include <MLinearLayoutPolicy>

// User includes.

#include "creporternotificationdialog.h"
#include "creporternamespace.h"

/*!
  * @class CReporterNotificationDialogPrivate
  * @brief Private CReporterNotificationDialog class.
  *
  */
class CReporterNotificationDialogPrivate
{
    public:
        //! @arg Crash report details from rich-core file name.
        QStringList details;
        //! @arg Server address.
        QString server;
        //! @arg Rich-core filesize.
        QString filesize;
        //! @arg Textfield widget.
        MTextEdit *commentField;
};

// *** Class CReporterNotificationDialog ****

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CReporterNotifyDialogPlugin::CReporterNotificationDialog
// ----------------------------------------------------------------------------
CReporterNotificationDialog::CReporterNotificationDialog(const QStringList &details,
                                                          const QString &server, const QString& filesize) :
        MDialog("", M::NoStandardButton),
        d_ptr(new CReporterNotificationDialogPrivate())
{
    Q_D(CReporterNotificationDialog);

    d->details = details;
    d->server = server;
    d->filesize = filesize;

    // Create widgets.
    createcontent();
}

// ----------------------------------------------------------------------------
// CReporterNotifyDialogPlugin::~CReporterNotificationDialog
// ----------------------------------------------------------------------------
CReporterNotificationDialog::~CReporterNotificationDialog()
{
    delete d_ptr;
    d_ptr = 0;
}

// ----------------------------------------------------------------------------
// CReporterNotifyDialogPlugin::userComments
// ----------------------------------------------------------------------------
QString CReporterNotificationDialog::userComments() const
{
    return d_ptr->commentField->text();
}

// ----------------------------------------------------------------------------
// CReporterNotifyDialogPlugin::createContent
// ----------------------------------------------------------------------------
void CReporterNotificationDialog::createcontent()
{
    Q_D(CReporterNotificationDialog);

    setObjectName("CrashReporterNotificationDialog");

    //% "The application %1 crashed."
    QString title = qtTrId("qtn_the_application_%1_crashed_text").arg(d->details.at(0));

    // Set title.
    setTitle(title);

    // Create widgets to be placed on central widget.
    QGraphicsWidget *panel = centralWidget();

    QString message;
    //% "Please help to improve the software by filling this report and describe what you we're doing."
    //% "<br>Useful information include how to reproduce the error etc."
    message = qtTrId("qtn_notify_dialog_header_text");

    // Central widget content.
    MLabel *upperLabel = new MLabel(message, panel);
    upperLabel->setWordWrap(true);
    upperLabel->setObjectName("DialogUpperLabel");

    d->commentField = new MTextEdit(MTextEditModel::MultiLine, "", panel);
    d->commentField->setObjectName("DialogCommentField");

    //% "File size: %1, Receiving server: %2"
    QString details = qtTrId("qtn_receiving_server_and_filesize_text").arg(d->filesize).arg(d->server);

    //% "The following technical information will be included in the report:<br> PID: %1, Signal: %2"
    details += "<br>" + qtTrId("qtn_technical_infomation_included_text")
                        .arg(d->details.at(3)).arg(d->details.at(2));

    MLabel *crashDetailsLabel = new MLabel(details, panel);
    crashDetailsLabel->setObjectName("CrashDetailsLabel");

    QSignalMapper *mapper = new QSignalMapper(this);

    //% "Options"
    MButton *optionsButton = new MButton(qtTrId("qtn_cr_options_button"), panel);
    optionsButton->setObjectName("DialogButton");
    optionsButton->setPreferredWidth(140);
    optionsButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    connect(optionsButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(optionsButton, static_cast<int>(CReporter::OptionsButton));

    // Layout for displaying server etc. details and options button.
    QGraphicsGridLayout *bottomLayout = new QGraphicsGridLayout;

    bottomLayout->addItem(crashDetailsLabel, 0, 0, Qt::AlignLeft | Qt::AlignTop);
    bottomLayout->addItem(optionsButton, 0, 1, Qt::AlignRight | Qt::AlignTop);

    // Create layout and policy.
    MLayout *layout = new MLayout(panel);
    panel->setLayout(layout);
    MLinearLayoutPolicy  *policy = new MLinearLayoutPolicy(layout, Qt::Vertical);
    policy->setObjectName("DialogMainLayout");

    // Add items to the layout.
    policy->addItem(upperLabel, Qt::AlignLeft | Qt::AlignTop);
    policy->addItem(d->commentField, Qt::AlignLeft  | Qt::AlignTop);
    policy->addItem(bottomLayout);
    //policy->addItem(crashDetailsLabel);

    // Add buttons to button area.
    //% "Send"
    MButtonModel *dialogButton = addButton(qtTrId("qtn_cr_button_send"));
    dialogButton->setObjectName("DialogButton");

    connect(dialogButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(dialogButton, static_cast<int>(CReporter::SendButton));

    //% "Delete"
    dialogButton = addButton(qtTrId("qtn_cr_button_delete"));
    dialogButton->setObjectName("DialogButton");

    connect(dialogButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(dialogButton, static_cast<int>(CReporter::DeleteButton));

    /*//% "Options"
    dialogButton = addButton(qtTrId("qtn_cr_options_button"));
    dialogButton->setObjectName("DialogButton");
    connect(dialogButton, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(dialogButton, static_cast<int>(CReporter::OptionsButton));*/

    connect(mapper, SIGNAL(mapped(int)), SIGNAL(actionPerformed(int)));
}

// End of file.