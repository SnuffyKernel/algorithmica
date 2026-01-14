#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include <functional>
#include <iostream>
#include <random>

#define MAX_SIZE_ARR 100000
#define MIN_SIZE_ARR 100

struct CommandArgs
{
	bool debug = false;
	bool not_do_print = false;
	size_t random_size = 0;
};

namespace Utils
{
	void swap(int &a, int &b);
	int is_integer(const std::string &str);
};

class CommandLine
{
public:
	CommandArgs parser(const int &argc, char *argv[]);
	void help_print(const std::string &name);
	void init_arr(int *&sort_arr, const int &random_n, int &n);
};

#endif // COMMAND_LINE_HPP