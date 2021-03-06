#include "atcnavfix.h"
#include <QDebug>

ATCNavFix::ATCNavFix(QString fixName, double latitude, double longitude) : ATCAbstractFix(latitude, longitude), name(fixName)
{
}

ATCNavFix::~ATCNavFix()
{
    if(scenePosition != nullptr) delete scenePosition;
    if(symbol != nullptr) delete symbol;
    if(label != nullptr) delete label;
}

QString ATCNavFix::getName()
{
    return name;
}

QAbstractGraphicsShapeItem *ATCNavFix::getSymbol()
{
    return symbol;
}

QPointF* ATCNavFix::getScenePosition()
{
    return scenePosition;
}

QGraphicsSimpleTextItem* ATCNavFix::getLabel()
{
    return label;
}

void ATCNavFix::setName(QString fixName)
{
    name = fixName;
}

void ATCNavFix::setSymbol(QAbstractGraphicsShapeItem *fixSymbol)
{
    symbol = fixSymbol;
}

void ATCNavFix::setScenePosition(QPointF *position)
{
    scenePosition = position;
}

void ATCNavFix::setLabel(QGraphicsSimpleTextItem *textLabel)
{
    label = textLabel;
}

void ATCNavFix::setColor(QColor color)
{
    QPen newPen(symbol->pen());
    newPen.setColor(color);

    symbol->setPen(newPen);
}

void ATCNavFix::show()
{
    if(symbol != nullptr) symbol->show();
    if(label != nullptr) label->show();

    visible = true;
}

void ATCNavFix::hide()
{
    if(symbol != nullptr) symbol->hide();
    if(label != nullptr) label->hide();

    visible = false;
}

bool ATCNavFix::isVisible()
{
    return visible;
}
