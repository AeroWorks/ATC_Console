#include "dialogtextconsole.h"
#include "ui_dialogtextconsole.h"
#include "atcconsolecommands.h"

#include <QDateTime>
#include <QTimer>
#include <QHash>
#include <QMouseEvent>
#include <QScrollBar>

DialogTextConsole::DialogTextConsole(QWidget *parent) :
    ATCDialog(parent, "Text Console", 800, 600, false, ATC::TextConsole),
    uiInner(new Ui::DialogTextConsole)
{
    uiInner->setupUi(this);
    windowSetup();
    consoleSetup();

    this->hide();
}

DialogTextConsole::~DialogTextConsole()
{
    delete uiInner;
}

void DialogTextConsole::printToConsole(QString command)
{
    QDateTime timeStamp = QDateTime::currentDateTime();
    uiInner->consoleDisplay->append("[" + timeStamp.toString("hh:mm") + "] >> " + command);
}

void DialogTextConsole::printToConsole(QStringList commandList) //DEBUG FCN
{
    foreach(QString command, commandList)
    {
        DialogTextConsole::printToConsole(command);
    }
}

void DialogTextConsole::setConsoleInputFocus()
{
    QTimer::singleShot(0, uiInner->consoleInput, SLOT(setFocus()));
}

void DialogTextConsole::on_consoleInput_returnPressed()
{
    QString commandString = getConsoleInputText();
    commandString = commandString.trimmed();

    if(!commandString.isEmpty())
    {
        clearConsoleInput();
        printToConsole(commandString);

        QString consoleReply = parseQuery(commandString);
        printToConsole(consoleReply);
    }
    else
    {
        clearConsoleInput();
        return;
    }
}

void DialogTextConsole::consoleSetup()
{
    uiInner->consoleDisplay->setFocusPolicy(Qt::ClickFocus);
    uiInner->consoleDisplay->setTextInteractionFlags(Qt::NoTextInteraction);

    connect(uiInner->consoleInput, SIGNAL(focussed(bool)), this, SLOT(raise()));
    connect(this, SIGNAL(closed()), this, SLOT(setSituationDisplayFocus()));
}

QString DialogTextConsole::getConsoleInputText()
{
    return uiInner->consoleInput->text();
}

void DialogTextConsole::clearConsoleInput()
{
    uiInner->consoleInput->clear();
}

QString DialogTextConsole::parseQuery(QString query)
{
    QStringList queryList = query.split(" ", QString::SkipEmptyParts);
    unsigned int argumentCount = countElements(queryList);

    enum CommandRepresentation
    {
        help,
        text,
        cmpd,
        dflt
    };

    QHash<QString, CommandRepresentation> commandOptions;

    commandOptions.insert("help", help);
    commandOptions.insert("text", text);
    commandOptions.insert("compound", cmpd);

    int switchController = commandOptions.value(queryList.at(0), dflt);

    switch (switchController) {
        case help:
            return ATCConsoleCommands::helpCommand();
            break;

        case text:
            return ATCConsoleCommands::textCommand();
            break;

        case cmpd:
            return ATCConsoleCommands::compoundCommand(argumentCount, queryList);
            break;

        default:
            return ATCConsoleCommands::defaultCommand();
            break;
    }
}

unsigned int DialogTextConsole::countElements(QStringList list)
{
    unsigned int elementCount = 0;

    foreach (QString element, list)
    {
        elementCount++;
    }

    return elementCount;
}

void DialogTextConsole::mousePressEvent(QMouseEvent *event)
{
    ATCDialog::mousePressEvent(event);
    setConsoleInputFocus();
}

void DialogTextConsole::setConsoleDisplayBottom()
{
    uiInner->consoleDisplay->verticalScrollBar()->setValue(uiInner->consoleDisplay->verticalScrollBar()->maximum());
}
