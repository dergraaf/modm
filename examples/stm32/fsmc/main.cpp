
#include <xpcc/architecture.hpp>
#include <xpcc/driver/ui/display/siemens_s75.hpp>

#include "fsmc.hpp"

// ----------------------------------------------------------------------------
GPIO__OUTPUT(Led, A, 8);
GPIO__INPUT(Button, C, 13);

using namespace xpcc::stm32;

namespace lcd
{
	GPIO__OUTPUT(D0,   D, 14);
	GPIO__OUTPUT(D1,   D, 15);
	GPIO__OUTPUT(D2,   D,  0);
	GPIO__OUTPUT(D3,   D,  1);
	GPIO__OUTPUT(D4,   E,  7);
	GPIO__OUTPUT(D5,   E,  8);
	GPIO__OUTPUT(D6,   E,  9);
	GPIO__OUTPUT(D7,   E, 10);

	typedef xpcc::gpio::Port<D7, D6, D5, D4, D3, D2, D1, D0> Port;

	GPIO__OUTPUT(Cs,    D,  7);		// Chip Select,     FSMC: NE1
	GPIO__OUTPUT(Cd,    E,  2);		// Command / Data,  FSMC: A23
	GPIO__OUTPUT(Wr,    D,  5);		// Write operation, FSMC: NWE

	GPIO__OUTPUT(Reset, E,  3);     // Reset, not FSMC

//	typedef xpcc::BitbangMemoryInterface<Port, Cs, Cd, Wr> Memory;
	typedef xpcc::stm32::FsmcExperimental Memory;
}

typedef xpcc::SiemensS75Landscape<lcd::Memory, lcd::Reset> Display;

Display display;

// ----------------------------------------------------------------------------

/**
 * Pin out for FSMC,
 * 100 pin
 *
 * Signal  STM   Port      PCB    Display Pin		Oszi
 * D0       61   PD14               6				LC0
 * D1       62   PD15              14				LC1
 * D2       81   PD 0              15				LC2
 * D3       82   PD 1              16
 * D4       38   PE 7              17
 * D5       39   PE 8              18
 * D6       40   PE 9              19
 * D7       41   PE10              20
 *
 * WR = NWE 86   PD 5              13				Ch1
 * CS = NE1	88   PD 7               3				Ch2
 * CD = A23  1   PE 2               1				LC3
 *
 * Reset         PE 3               2
 *
 */

// ----------------------------------------------------------------------------
MAIN_FUNCTION
{
	// Switch STM32F4 to 168 MHz (HSE clocked by an 25 MHz external clock)
	if (Clock::enableHse(Clock::HseConfig::HSE_BYPASS)) {
		Clock::enablePll(Clock::PllSource::PLL_HSE, 25, 336);
		Clock::switchToPll();
	}
	
	Led::setOutput(true);
	Button::setInput(xpcc::stm32::PULLUP);

	// -------------
//	typedef xpcc::stm32::FsmcExperimental fsmc;
//
//	fsmc::initialize();
//
//	uint16_t ii = 0;
//	while (1)
//	{
//		fsmc::writeData(ii++);
//		fsmc::writeRegister(ii++);
////		fsmc::writeRegister(ii++);
////		fsmc::writeRegister(ii++);
////		fsmc::writeRegister(ii++);
//
//		Led::toggle();
//
//		xpcc::delay_ms(100);
//	}

	// -------------

	// Do not set to output when using as FSMC
//		lcd::Port::setOutput();

	display.initialize();
	display.setFont(xpcc::font::Assertion);

	while (1) {
		static uint8_t x = 0;
		display.clear();
		display.setCursor(x, 5);
		display << "Hello";
		display.setCursor(46, 24);
		display << "World! abcdefghijk";

		// finished, copy to LCD
		// Drawingtime with FSMC: 14 msec
		Led::set();
		display.update();
		Led::reset();

		xpcc::delay_ms(10);

		if (++x > 170)
		{
			x = 0;
		}
	}
}
