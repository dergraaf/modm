// coding: utf-8
/*
 * Copyright (c) 2017, Sascha Schade
 * Copyright (c) 2018, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include "mcp2515_can_bit_timings_test.hpp"

#include <modm/architecture/interface/clock.hpp>
#include <modm/driver/can/mcp2515_bit_timings.hpp>

using namespace modm;
using namespace modm::literals;

#define TEST_TIMING(clk, bitrate, sjw, prop, ps1, ps2, prescaler) \
	TEST_ASSERT_EQUALS((modm::CanBitTimingMcp2515<clk, Can::Bitrate::bitrate>::getSJW()), sjw); \
	TEST_ASSERT_EQUALS((modm::CanBitTimingMcp2515<clk, Can::Bitrate::bitrate>::getProp()), prop); \
	TEST_ASSERT_EQUALS((modm::CanBitTimingMcp2515<clk, Can::Bitrate::bitrate>::getPS1()), ps1); \
	TEST_ASSERT_EQUALS((modm::CanBitTimingMcp2515<clk, Can::Bitrate::bitrate>::getPS2()), ps2); \
	TEST_ASSERT_EQUALS((modm::CanBitTimingMcp2515<clk, Can::Bitrate::bitrate>::getPrescaler()), prescaler);

void
Mcp2515CanBitTimingsTest::testPrecalculatedValues()
{
	//          Clock  Baud    SJW Prop PS1 PS2 Prescaler
	TEST_TIMING(8_MHz,  kBps10,   1,   1,  4,  2,  100);
	TEST_TIMING(8_MHz,  kBps20,   1,   1,  4,  2,   50);
	TEST_TIMING(8_MHz,  kBps125,  1,   1,  4,  2,    8);
	TEST_TIMING(8_MHz,  kBps250,  1,   1,  4,  2,    4);
	TEST_TIMING(8_MHz,  kBps500,  1,   1,  4,  2,    2);
	TEST_TIMING(8_MHz,  MBps1,    1,   1,  1,  1,    2);

	//          Clock  Baud    SJW Prop PS1 PS2 Prescaler
	TEST_TIMING(16_MHz, kBps10,   1,   3,  8,  4,  100);
	TEST_TIMING(16_MHz, kBps20,   1,   3,  8,  4,   50);
	TEST_TIMING(16_MHz, kBps125,  1,   3,  8,  4,    8);
	TEST_TIMING(16_MHz, kBps250,  1,   3,  8,  4,    4);
	TEST_TIMING(16_MHz, kBps500,  1,   3,  8,  4,    2);
	TEST_TIMING(16_MHz, MBps1,    1,   1,  4,  2,    2);

	//          Clock  Baud    SJW Prop PS1 PS2 Prescaler
	TEST_TIMING(20_MHz, kBps10,   3,   5,  8,  4,  100);
	TEST_TIMING(20_MHz, kBps20,   3,   5,  8,  4,   50);
	TEST_TIMING(20_MHz, kBps125,  3,   5,  8,  4,    8);
	TEST_TIMING(20_MHz, kBps250,  3,   5,  8,  4,    4);
	TEST_TIMING(20_MHz, kBps500,  3,   5,  8,  4,    2);
	TEST_TIMING(20_MHz, MBps1,    1,   3,  4,  2,    2);
}

