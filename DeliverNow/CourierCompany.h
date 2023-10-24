#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_DeliverNow.h"
#include "ui_Widget.h"
#include "Observer.h"
#include"PackageService.h"
#include "Courier.h"
#include<qmessagebox.h>
class CourierCompany : public QWidget, public Observer {
	Q_OBJECT

public:
	CourierCompany(PackageService& service, QWidget* parent = nullptr) : service{ service }, QWidget( parent ) {
		ui.setupUi(this);
		this->setWindowTitle("Courier Company");
		this->populateList();
		QPushButton::connect(this->ui.addPackage, &QPushButton::clicked, [this]() {
			this->addPackage();
			});
	};

	void addPackage()
	{
		if (this->ui.recipientEdit->text().size() == 0)
		{
			QMessageBox b{};
			b.critical(this, "Error adding", "Please add a recipient!");
			return;
		}
		s rec = this->ui.recipientEdit->text().toStdString();
		s street = this->ui.streetEdit->text().toStdString();
		int nr = this->ui.numberEdit->text().toInt();
		int x = this->ui.xEdit->text().toInt();
		int y = this->ui.yEdit->text().toInt();
		if (x < 0 || y < 0 || nr < 0)
		{
			QMessageBox b{};
			b.critical(this, "Error adding", "Please add positive coordinates!");
			return;
		}
		Package p{ rec,street,nr,x,y,"false" };
		this->service.AddPackage(p);
		this->service.notify();
	}

	void update() {
		this->populateList();
	}
	void populateList() {
		this->ui.listWidget->clear();
		std::vector<Package> packages = this->service.getAll();
		for (Package p : packages)
		{
			s del = "false";
			if (p.getDelivered())
				del = "true";
			QListWidgetItem* t = new QListWidgetItem{ QString::fromStdString(p.getRecipient() + ";" + p.getStreet() + ";" + std::to_string(p.getNumber()) + ";" + std::to_string(p.getX()) + " " + std::to_string(p.getY()) + " " + del) };
			if (del == "true")
				t->setBackground(Qt::green);
			this->ui.listWidget->addItem(t);

		}
	}
private:
	Ui::Form ui;
	PackageService& service;
};