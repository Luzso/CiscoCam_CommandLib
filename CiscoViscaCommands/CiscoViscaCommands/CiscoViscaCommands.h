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

	int completeCommand(byte* commandBytes, int nCommandBytes, byte** arrayOut);


	/// <summary>
	/// Turn the power light on the camera on or off.
	/// </summary>
	/// <param name="on"></param>
	/// <param name="arrayOut"></param>
	/// <returns></returns>
	int setPowerLED(power_led state, byte** arrayOut) {
		static byte powerLight[] = { 0x01, 0x01, 0x33, 0x02, (unsigned char)state };
		static const int commandSize = sizeof(powerLight) / sizeof(byte);

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
		static const int commandSize = sizeof(callLight)/sizeof(byte);

		return completeCommand(callLight, commandSize, arrayOut);
	}





	
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