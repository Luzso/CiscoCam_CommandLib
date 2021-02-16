#include "pch.h"
#include "CppUnitTest.h"
#include "CiscoViscaCommands.h"
#include <iostream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CommandTests
{
	using byte = unsigned char;
	using namespace cisco_commands;

	TEST_CLASS(CommandTests)
	{
	public:
		

		TEST_METHOD(TestOnoffCommand)
		{
			byte* onOffArray = NULL;
			int size = cisco_commands::setPowerLED(power_led::on, &onOffArray);

			int testSize = sizeof(unsigned char);
			std::cout << "First element: " << onOffArray[0];

			Logger::WriteMessage("Assert elements in returned array");
			Assert::IsTrue(onOffArray[0] == 0x81, L"First element");
			Assert::IsTrue(onOffArray[1] == 0x01, L"Seconds element");
			Assert::IsTrue(size == 7);
		}

		TEST_METHOD(TestResetPos) {
			byte* arrayOut = NULL;
			int size = cisco_commands::resetPos(&arrayOut);

			Assert::IsTrue(size == 5);
		}

		TEST_METHOD(TestPanSpeed) {

			// Pan left
			byte* arrayOut = NULL;
			int size = cisco_commands::moveStart(pan_mode::left, tilt_mode::none, 5, 0, &arrayOut);

			Assert::IsTrue(arrayOut[6] == 0x01); // Pan left
			Assert::IsTrue(arrayOut[7] == 0x03); // No tilt
			Assert::IsTrue(arrayOut[4] == 0x05); // Pan speed 5
			Assert::IsTrue(arrayOut[5] == 0x00); // Tilt speed 0

		}

	};
}
