#pragma once

#include "gtest/gtest.h"
#include <chrono>

#define LOG_MAX_BYTE ((off_t)(1 << 30))
#define LOG_MAX_OPS 81920
#define PMEM_ROOT "D:/pmem-fs"

#define GET_TIME_STAMP_US                                                      \
	std::chrono::duration_cast<std::chrono::microseconds>(                 \
		std::chrono::system_clock::now().time_since_epoch())           \
		.count()

class TimeTest : public testing::Test {
protected:
	TimeTest()
	{
		// You can do set-up work for each test here.
	}

	~TimeTest() override
	{
		// You can do clean-up work that doesn't throw exceptions here.
	}

	// If the constructor and destructor are not enough for setting up
	// and cleaning up each test, you can define the following methods:

	void
	SetUp() override
	{
		// Code here will be called immediately after the constructor
		// (right before each test).
		_start = GET_TIME_STAMP_US;
	}

	void
	TearDown() override
	{
		// Code here will be called immediately after each test (right
		// before the destructor).
		printf("[          ] using %ld us.\n",
		       (GET_TIME_STAMP_US - _start));
	}

	long _start;
	// Objects declared here can be used by all tests in the test case for
	// Foo.
};
