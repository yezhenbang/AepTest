#include <fstream>
#include <iostream>
#include "test.h"
using namespace std;

TEST_F(TimeTest, fstream_io)
{
	fstream file;
	file.open("D:\\pmem-fs\\log.dat", ios::app);

	const char *str = "This is a \n";
	for (int i = 0; i < LOG_CNT; i++)
		file << str;

	printf("fstream���%d����־��\n", LOG_CNT);
	// �رմ򿪵��ļ�
	file.close();
	EXPECT_EQ(1, 1);
}