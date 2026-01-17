#include "command_line.hpp"

CommandArgs CommandLine::parser(const int &argc, char *argv[])
{
	CommandArgs commandArgs;
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];

		if (arg == "-h" || arg == "--help")
		{
			help_print(argv[0]);
		}
		else if (arg == "-d" || arg == "--debug")
		{
			commandArgs.debug = true;
		}
		else if (arg == "-np" || arg == "--do_no_print")
		{
			commandArgs.not_do_print = true;
		}
		else if (arg == "-r" || arg == "--random")
		{
			if (i + 1 < argc)
			{
				arg = argv[++i];
				int digit = Utils::is_integer(arg);

				if (digit && digit <= MAX_SIZE_ARR && digit >= MIN_SIZE_ARR)
				{
					commandArgs.random_size = digit;
				}
				else
				{
					std::cout << "This argument: " << arg << " must be the number <= " << MAX_SIZE_ARR << " and >= " << MIN_SIZE_ARR << std::endl;
				}
			}
			else
			{
				std::cout << "Not enough arguments! " << arg << std::endl;
				std::cout << "-r [size] or --random [size]"<< std::endl;
				std::cout << " size <= " << MAX_SIZE_ARR << " and >= " << MIN_SIZE_ARR << std::endl;
			}
		}
		else
		{
			std::cout << "Unknown argument: " << arg << std::endl;
			help_print(argv[0]);
		}
	}

	return commandArgs;
}

void CommandLine::help_print(const std::string &name)
{
	std::cout << "Usage: " << name << " [options]" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "	-d  or --debug       ---> out running time of the algorithm" << std::endl;
	std::cout << "	-np or -do_no_print  ---> do not print a sorted array " << std::endl;
	std::cout << "	-r  or --random      ---> generates random numbers" << std::endl;
	std::cout << "		size array" << " must be the number <= " << MAX_SIZE_ARR << " and >= " << MIN_SIZE_ARR << std::endl;
	std::cout << "		EXAMPLE: -r 100 or --random 10000" << std::endl;
	std::cout << "	-h  or --help         ---> out help" << std::endl;
}


void CommandLine::init_arr(int *&sort_arr, const size_t &random_n, int &n)
{
	if (random_n)
	{
		n = random_n;
		sort_arr = new int[n];

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, random_n * random_n);

		for (int i = 0; i < n; i++)
		{
			sort_arr[i] = dist(gen);
		}
	}
	else
	{
		n = 10;
		sort_arr = new int[n]{2, 10, 5, 7, 3, 9, 8, 1, 6, 4};
	}
}

void Utils::swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

int Utils::is_integer(const std::string &str)
{
	try
	{
		std::size_t pos = 0;
		int digit = std::stoi(str, &pos);

		if (pos == str.length())
		{
			return digit;
		}
		else
		{
			return 0;
		}
	}
	catch (...)
	{
		return 0;
	}
}