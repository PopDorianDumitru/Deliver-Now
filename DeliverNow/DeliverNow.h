#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DeliverNow.h"
#include "Observer.h"
#include"PackageService.h"
#include "Courier.h"
#include<qmessagebox.h>
class DeliverNow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    DeliverNow(Courier c, PackageService& service,QWidget *parent = nullptr);
    ~DeliverNow();
    void update() {
        this->populateList();
        std::vector<s>streets = this->service.getStreets();
        for (s str : streets)
        {
            if (this->ui.comboBox->findText(QString::fromStdString(str)) == -1)
                this->ui.comboBox->addItem(QString::fromStdString(str));
        }
        /*this->ui.comboBox->clear();
        this->ui.comboBox->addItem(QString::fromStdString(""));

        for (s stre : streets)
        {
            this->ui.comboBox->addItem(QString::fromStdString(stre));
        }*/
    }
    void populateList() {
        this->ui.listWidget->clear();
        std::vector<Package> packages;

        if (this->ui.comboBox->currentText() == "")
        {
            packages = this->service.getUndelivered(this->c);
        }
        else
            packages = this->service.getByStreet(this->c, this->ui.comboBox->currentText().toStdString());
        for (Package p : packages)
        {
            s del = "false";
            if (p.getDelivered())
                del = "true";
            this->ui.listWidget->addItem(QString::fromStdString( p.getRecipient() + ";" + p.getStreet() + ";" + std::to_string(p.getNumber()) + ";" + std::to_string(p.getX()) + " " + std::to_string(p.getY()) + " " + del));
        }
    }
    void deliver() {
        if (this->ui.listWidget->selectedItems().size() == 0)
        {
            QMessageBox b{};
            b.critical(this, "Error delivering", "Please select a package!");
            return;
        }
        s g = this->ui.listWidget->selectedItems()[0]->text().toStdString();
        std::stringstream str(g);
        std::vector<s>  tokens;
        while (!str.eof())
        {
            s temp;
            std::getline(str,temp, ';');
            tokens.push_back(temp);
        }
        Package& t = this->service.getPackage(tokens[1], std::stoi(tokens[2]));
        t.setDelivered();
        this->service.notify();
    }

private:
    Ui::DeliverNowClass ui;
    Courier c;
    PackageService& service;
};
