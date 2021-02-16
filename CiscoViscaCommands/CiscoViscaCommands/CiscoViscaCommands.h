#pragma once


namespace cisco_commands {

	using byte = unsigned char;

	enum class power_led : byte {
		off,
		on
	};

	enum class call_led : byte{
		off,
		on,
		blink
	};

	enum class zoom_mode : byte {
		stop = 0,
		tele = 2,
		wide
	};

	enum class focus_mode : byte {
		stop = 0,
		far = 2,
		near
	};

	enum class pan_mode : byte {
		left = 0x01,
		right,
		none
	};

	enum class tilt_mode : byte {
		up = 0x01,
		down,
		none
	};

	int completeCommand(byte* commandBytes, int nCommandBytes, byte** arrayOut);


	/// <summary>
	/// Turn the power light on the camera on or off.
	/// </summary>
	/// <param name="on"></param>
	/// <param name="arrayOut"></param>
	/// <returns></returns>
	int setPowerLED(power_led state, byte** arrayOut) {
		static byte powerLight[] = { 0x01, 0x01, 0x33, 0x02, (unsigned char)state };
		static const int commandSize = sizeof(powerLight);

		return completeCommand(powerLight, commandSize, arrayOut);
	}


	/// <summary>
	/// Turn the Call LED on or off
	/// </summary>
	/// <param name="state"></param>
	/// <param name="arrayOut"></param>
	/// <returns></returns>
	int setCallLED(call_led state, byte** arrayOut) {
		static byte callLight[] = { 0x01, 0x01, 0x33, 0x01, (unsigned char)state };
		static const int commandSize = sizeof(callLight);

		return completeCommand(callLight, commandSize, arrayOut);
	}

	/// <summary>
	/// Set the mirror state of the camera.
	/// </summary>
	/// <param name="state"></param>
	/// <param name="arrayOut"></param>
	/// <returns></returns>
	int mirrorCam(bool state, byte** arrayOut) {
		static byte mirror[] = { 0x01, 0x04, 0x33, 0x01 + (int)state };
		static const int commandSize = sizeof(mirror);

		return completeCommand(mirror, commandSize, arrayOut);
	}


	/// <summary>
	/// Start the zoom action of the camera.
	/// </summary>
	/// <param name="zoomMode"></param>
	/// <param name="speed"></param>
	/// <param name="arrayOut"></param>
	/// <returns></returns>
	int zoom(zoom_mode zoomMode, int speed, byte** arrayOut) {

		// Cap input speed to max value, byte is unsigned char so it can't be negative
		byte maxSpeed = 0x0f;
		if (speed > maxSpeed)
			speed = maxSpeed;

		static byte zoom[] = { 0x01, 0x04, 0x07, (byte)zoomMode + speed };
		static const int commandSize = sizeof(zoom);

		return completeCommand(zoom, commandSize, arrayOut);
	}


	/// <summary>
	/// Start the focus action of the camera.
	/// </summary>
	int focus(focus_mode focusMode, byte speed, byte** arrayOut) {
		// Cap input speed to max value, byte is unsigned char so it can't be negative
		byte maxSpeed = 0x0f;
		if (speed > maxSpeed)
			speed = maxSpeed;

		static byte focus[] = { 0x01, 0x04, 0x08, (byte)focusMode + speed };
		static const int commandSize = sizeof(focus);

		return completeCommand(focus, commandSize, arrayOut);
	}


	/// <summary>
	/// Reset the position of the camera to the default position
	/// </summary>
	int resetPos(byte** arrayOut) {
		static byte reset[] = { 0x01, 0x06, 0x05 };
		static const int commandSize = sizeof(reset);

		return completeCommand(reset, commandSize, arrayOut);
	}


	
	/// <summary>
	/// Stop the movement of the camera.
	/// </summary>
	int moveStop(byte** arrayOut) {
		static byte stop[] = { 0x01, 0x06, 0x01, 0x03, 0x03, 0x03, 0x03 };
		static const int commandSize = sizeof(stop);

		return completeCommand(stop, commandSize, arrayOut);
	}


	/// <summary>
	/// Start the movement of the camera
	/// </summary>
	int moveStart(pan_mode panMode, tilt_mode tiltMode, int panSpeed, int tiltSpeed, byte** arrayOut) {

		// Cap input values
		int maxPanSpeed = 0x0f;
		int maxTiltSpeed = 0x0f;
		if(panSpeed > maxPanSpeed)
			panSpeed = maxPanSpeed;
		if (tiltSpeed > maxTiltSpeed)
			tiltSpeed = maxTiltSpeed;

		static byte move[] = { 0x01, 0x06, 0x01, (byte)panSpeed, (byte)tiltSpeed, (byte)panMode, (byte)tiltMode };
		static const int commandSize = sizeof(move);

		return completeCommand(move, commandSize, arrayOut);
	}


	// TODO: Move to set position
	

	/// <summary>
	/// Complete any Cisco VISCA command by prepending the command with an address and appending it with the terminator byte.
	/// </summary>
	int completeCommand(byte* commandBytes, int nCommandBytes, byte** arrayOut) {
		
		// Make room for the full command in memory
		static byte address = 0x81;
		static byte fullCommand[16] = { address }; // Cisco PrecisionHD user guide states the full command can range between 3 and 16 bytes

		// Insert the command after the address
		memcpy(fullCommand + 1, commandBytes, nCommandBytes);

		// Append with the terminator byte		
		fullCommand[1 + nCommandBytes] = 0xff;

		// Set the output of the function to the resulting array.
		*arrayOut = fullCommand;

		// Total size of the byte array
		int nTotalBytes = 1 + nCommandBytes + 1; // address + command + terminator bytess
		return nTotalBytes;
	}
}