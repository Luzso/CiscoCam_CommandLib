#pragma once

#include <QObject>
#include <QSerialPort>

class CiscoBackend : public QObject
{
	Q_OBJECT

public:
	CiscoBackend(QObject *parent = NULL);
	~CiscoBackend();

	bool isConnected = false;

	void togglePowerLED();

	void toggleCallLED();

	bool connectToDevice();


private:

	QSerialPort* serial = NULL;


	void configurePort();
};
