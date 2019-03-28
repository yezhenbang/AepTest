#include <fstream>
#include <iostream>
#include "test.h"
using namespace std;

double
test_fread(const char *path, int block_size)
{
	fstream file;
	file.open(path, ios::in);
	char *buf = (char *)malloc(block_size);

	int cnt = LOG_MAX_BYTE / block_size;
	if (cnt > LOG_MAX_OPS)
		cnt = LOG_MAX_OPS;

	long _start = GET_TIME_STAMP_US;

	for (int i = 0; i < cnt; ++i) {
		file.read(buf, block_size);
	}
	long dur = GET_TIME_STAMP_US - _start;
	free(buf);
	file.close();
	// return static_cast<double>(cnt) * block_size / dur; // M/s
	printf("test-read block_size :%5d : %.3f M/s.\n", block_size,
	       static_cast<double>(cnt) * block_size / dur);
	return 1;
}

double
test_fwrite(const char *path, int block_size)
{
	fstream file;
	file.open(path, ios::trunc|ios::out);
	char *buf = (char *)malloc(block_size);
	
	int cnt = LOG_MAX_BYTE / block_size;
	if (cnt > LOG_MAX_OPS)
		cnt = LOG_MAX_OPS;

	long _start = GET_TIME_STAMP_US;

	for (int i = 0; i < cnt; ++i) {
		file.write(buf, block_size);
	}

	long dur = GET_TIME_STAMP_US - _start;
	free(buf);
	file.close();
	// return static_cast<double>(cnt) * block_size / dur; // M/s
	printf("test-write block_size:%5d : %.3f M/s.\n", block_size,
	       static_cast<double>(cnt) * block_size / dur);
	return 1;
}

double
test_fwrite_flush(const char *path, int block_size)
{
	fstream file;
	file.open(path, ios::trunc | ios::out);
	char *buf = (char *)malloc(block_size);

	int cnt = LOG_MAX_BYTE / block_size;
	if (cnt > LOG_MAX_OPS)
		cnt = LOG_MAX_OPS;

	long _start = GET_TIME_STAMP_US;

	for (int i = 0; i < cnt; ++i) {
		file.write(buf, block_size);
		file.flush();
	}

	long dur = GET_TIME_STAMP_US - _start;
	free(buf);
	file.close();
	// return static_cast<double>(cnt) * block_size / dur; // M/s
	printf("test-flush-write block_size:%5d : %.3f M/s.\n", block_size,
	       static_cast<double>(cnt) * block_size / dur);
	return 1;
}


TEST(IOTest, fstream_io)
{
	std::string path = PMEM_ROOT + (std::string)"/log.dat";
	test_fwrite(path.c_str(), (32));
	test_fwrite(path.c_str(), (1 << 10));
	test_fwrite(path.c_str(), 4*(1 << 10));
	test_fwrite_flush(path.c_str(), (32));
	test_fwrite_flush(path.c_str(), (1 << 10));
	test_fwrite_flush(path.c_str(), 4 * (1 << 10));
	test_fread(path.c_str(), (32));
	test_fread(path.c_str(), (1 << 10));
	test_fread(path.c_str(), 4*(1 << 10));

	EXPECT_EQ(1, 1);
}