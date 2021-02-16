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


	/// <summary>
	/// Turn the power light on the camera on or off.
	/// </summary>
	/// <param name="on"></param>
	/// <param name="arrayOut"></param>
	/// <returns></returns>
	int setPowerLED(power_led state, byte** arrayOut) {
		static byte powerLight[] = { 0x01, 0x33, 0x02, (unsigned char)state };
		*arrayOut = powerLight;
		return sizeof(powerLight) / sizeof(byte);
	}


	/// <summary>
	/// Turn the Call LED on or off
	/// </summary>
	/// <param name="state"></param>
	/// <param name="arrayOut"></param>
	/// <returns></returns>
	int setCallLED(call_led state, byte** arrayOut) {
		static byte callLight[] = { 0x01, 0x33, 0x01, (unsigned char)state };
		*arrayOut = callLight;
		return sizeof(callLight)/sizeof(byte);
	}

	int completeCommand(byte** commandBytes, int nCommandBytes) {


		return nCommandBytes;
	}
}