#include "atcsituationaldisplay.h"
#include "mainwindow.h"

#include <QWheelEvent>
#include <QCursor>
#include <QGuiApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>

ATCSituationalDisplay::ATCSituationalDisplay(QWidget *parent) : QGraphicsView(parent), airspaceData(new ATCAirspace)
{
    situationalDisplaySetup();
    loadData();
}

ATCSituationalDisplay::~ATCSituationalDisplay()
{
    delete airspaceData;
}

qreal ATCSituationalDisplay::getBaseScale() const
{
    return baseScale;
}

void ATCSituationalDisplay::setBaseScale(qreal scale)
{
    baseScale = scale;
}

void ATCSituationalDisplay::situationalDisplaySetup()
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setDragMode(QGraphicsView::NoDrag);
    setSceneRect(-50000, -50000, 100000, 100000);

    viewport()->setCursor(Qt::CrossCursor);

    scene = new QGraphicsScene(this);
    setScene(scene);

    QBrush brush(Qt::gray);

    QPen pen(Qt::green);
    pen.setWidth(3);

    QPen penLine(Qt::white);
    penLine.setWidth(5);

    rect1 = scene->addRect(-250, -250, 100, 100, pen, brush);
    rect2 = scene->addRect(-250, 150, 100, 100, pen, brush);
    rect3 = scene->addRect(150, 150, 100, 100, pen, brush);
    rect4 = scene->addRect(150, -250, 100, 100, pen, brush);

    lineH = scene->addLine(-25, 0, 25, 0, penLine);
    lineV = scene->addLine(0, -25, 0, 25, penLine);
}

void ATCSituationalDisplay::loadData()
{    
    QFile sectorFile("E:/Qt/ATC_Console/ATC_Console/EPWA_TMA.txt");

    if(!sectorFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Error while opening data file...";
        return;
    }

    QTextStream inStream(&sectorFile);
    while(!inStream.atEnd())
    {
        QString textLine = inStream.readLine();
        textLine = textLine.trimmed();

        if(textLine.contains("SECTORLINE", Qt::CaseInsensitive))
        {
            QStringList stringList = textLine.split(":", QString::SkipEmptyParts);
            QString sectorName = stringList[1];

            airspaceData->appendSector(new ATCAirspaceSector(sectorName));
            qDebug() << "Sector " + sectorName + " appended...";
        }
        else if(textLine.contains("COORD", Qt::CaseInsensitive))
        {
            QStringList stringList = textLine.split(":", QString::SkipEmptyParts);
            QString latitudeString = stringList[1];
            QString longitudeString = stringList[2];

            double latitudeDouble = airspaceData->coordsStringToDouble(latitudeString);
            double longitudeDouble = airspaceData->coordsStringToDouble(longitudeString);

            airspaceData->getLastSector()->appendAirspaceFix(new ATCAirspaceFix(latitudeDouble, longitudeDouble));
        }
    }

    sectorFile.close();
}

void ATCSituationalDisplay::wheelEvent(QWheelEvent *event)
{
    if(QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier))
    {
        QPoint numDegrees = event->angleDelta();
        qreal newScale = baseScale + (numDegrees.y() / 120) * scaleResolution;

        scale(newScale, newScale);
    }

    event->accept();
}

void ATCSituationalDisplay::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void ATCSituationalDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if(QGuiApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier))
    {
        QGraphicsView::mouseMoveEvent(event);
    }
    event->accept();
}

void ATCSituationalDisplay::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void ATCSituationalDisplay::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        this->setDragMode(QGraphicsView::ScrollHandDrag);
    }
    event->accept();
}

void ATCSituationalDisplay::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        this->setDragMode(QGraphicsView::NoDrag);
        viewport()->setCursor(Qt::CrossCursor);        
    }
    event->accept();
}
