#include "CiscoBackend.h"
#include "CiscoViscaCommands.h"
#include <QSerialPortInfo>

using namespace cisco_commands;

CiscoBackend::CiscoBackend(QObject *parent)
	: QObject(parent)
{
	this->serial = new QSerialPort(this);
	this->configurePort();
	this->connectToDevice();

}

CiscoBackend::~CiscoBackend()
{
	this->serial->close();
}



void CiscoBackend::togglePowerLED()
{
	static power_led status = power_led::on; // LED is on by default, in future maybe request led status

	status = (power_led)(1 - (byte)status);
	byte* commandBytes;
	qint64 nBytes = cisco_commands::setPowerLED(status, &commandBytes);

	if(this->isConnected)
		this->serial->write((char*)commandBytes, nBytes);
}


void CiscoBackend::toggleCallLED() {
	static call_led status = call_led::off; // LED is on by default, in future maybe request led status

	status = (call_led)(1 - (byte)status);
	byte* commandBytes;
	qint64 nBytes = cisco_commands::setCallLED(status, &commandBytes);

	if (this->isConnected)
		this->serial->write((char*)commandBytes, nBytes);
}

bool CiscoBackend::connectToDevice()
{
	// Get available serial ports
	QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

	if (availablePorts.count() > 0) {
		for each(auto port in availablePorts){
			
			QString desc = port.description();
			QString portName = port.portName();
			quint16 pID;
			quint16 vID;
			if (port.hasProductIdentifier())
				pID = port.productIdentifier();
			if (port.hasVendorIdentifier())
				vID = port.vendorIdentifier();

			bool isUART = desc.contains("UART");
			if (isUART) {

				this->serial->setPort(port);
				this->isConnected = this->serial->open(QIODevice::ReadWrite);

				// Test connection

				break;
			}

		}
	}

	return false;
}


void CiscoBackend::configurePort() {


	if (this->serial != NULL) {
		this->serial->setBaudRate(9600);
		this->serial->setDataBits(QSerialPort::DataBits::Data8);
		this->serial->setParity(QSerialPort::Parity::NoParity);
		this->serial->setStopBits(QSerialPort::StopBits::OneStop);
		this->serial->setFlowControl(QSerialPort::NoFlowControl);
	}
}


