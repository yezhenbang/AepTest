// aeptest.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}
