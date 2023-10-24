#include "DeliverNow.h"

DeliverNow::DeliverNow(Courier c,PackageService& service,QWidget *parent)
    : QMainWindow(parent), c{ c }, service{service}
{
    ui.setupUi(this);
    this->setWindowTitle(QString::fromStdString(c.getName()));
    this->ui.label->setText(QString::fromStdString("ZONE: X-" + std::to_string(c.getX()) + " Y-" + std::to_string(c.getY()) + " R-" + std::to_string(c.getR())));
    this->populateList();
    QComboBox::connect(this->ui.comboBox, &QComboBox::currentIndexChanged, [this]() {
        this->populateList();
        });
    std::vector<s> streets = this->service.getStreets();
    this->ui.comboBox->addItem(QString::fromStdString(""));

    for (s stre : streets)
    {
        this->ui.comboBox->addItem(QString::fromStdString(stre));
    }
    QPushButton::connect(this->ui.pushButton, &QPushButton::clicked, [this]() {
        this->deliver();
        });
}

DeliverNow::~DeliverNow()
{}
