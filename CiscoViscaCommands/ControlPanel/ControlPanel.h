#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ControlPanel.h"

class ControlPanel : public QMainWindow
{
    Q_OBJECT

public:
    ControlPanel(QWidget *parent = Q_NULLPTR);

private:
    Ui::ControlPanelClass ui;
};
