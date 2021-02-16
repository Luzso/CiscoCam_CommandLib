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
			Assert::IsTrue(onOffArray[0] == 0x01, L"First element");
			Assert::IsTrue(onOffArray[1] == 0x33, L"Seconds element");
		}
	};
}
