#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DeliverNow.h"
#include "ui_Widget.h"
#include "Observer.h"
#include <qpainter.h>
#include"PackageService.h"
#include "Courier.h"

class Map: public QWidget, public Observer {
 Q_OBJECT
public:
    void paintEvent(QPaintEvent*)
    {
        QPainter painter(this);
        painter.setPen(Qt::blue);
        painter.setFont(QFont("Arial", 30));
        std::vector<Package> packs = this->service.getAll();
        for (Package p : packs)
        {
            if (!p.getDelivered())
            {
                painter.drawRect(p.getX(), p.getY(), 5, 5);
            }
        }
    }
    void update() {
        this->repaint();
    }
    Map( PackageService& service, QWidget* parent = nullptr)
        : QWidget(parent),service{ service }
    {
        this->setWindowTitle("Map");
    }
private:
    PackageService& service;
};