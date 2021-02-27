#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControlPanel.h"
#include "CiscoBackend.h"

class ControlPanel : public QMainWindow
{
    Q_OBJECT

public:
    ControlPanel(QWidget *parent = Q_NULLPTR);

private:
    Ui::ControlPanelClass ui;

    CiscoBackend backend;

    void setConnections() {

        // Power LED
        this->connect(
            ui.btnPowerLED,
            &QPushButton::released,
            this,
            &ControlPanel::onBtn_PowerLED);

        // Call LED
        this->connect(
            ui.btnCallLED,
            &QPushButton::released,
            this,
            &ControlPanel::onBtn_callLED);
    }


private slots:
    void onBtn_PowerLED() {
        this->backend.togglePowerLED();
    }

    void onBtn_callLED() {
        this->backend.toggleCallLED();
    }
};
