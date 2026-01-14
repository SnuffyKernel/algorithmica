#include <iostream>
#include <chrono>
#include <functional>

#include "sorting.hpp"

Timer::Timer(const std::string &name, const bool &_debug) : func_name(name), debug(_debug)
{
	start_time = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
	if (debug)
	{
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

		std::cout << func_name << " took: " << duration.count() << " microsec";
		std::cout << " (" << duration.count() / 1000.0 << " ms)\n";
	}
}

Sorting::Sorting(const bool &_debug) : debug(_debug) {}

void Sorting::bubble_sort(int *a, int n)
{
	TIMER();

	for (int k = 0; k < n - 1; k++)
	{
		for (int i = 0; i < n - 1 - k; i++)
		{
			if (a[i] > a[i + 1])
			{
				Utils::swap(a[i], a[i + 1]);
			}
		}
	}
}

void Sorting::selection_sort(int *a, int n)
{
	TIMER();

	for (int k = 0; k < n - 1; k++)
		for (int j = k + 1; j < n; j++)
			if (a[k] > a[j])
				Utils::swap(a[j], a[k]);
}

void Sorting::insertion_sort(int *a, int n)
{
	TIMER();

	for (int k = 1; k < n; k++)
		for (int i = k; i > 0 && a[i] < a[i - 1]; i--)
			Utils::swap(a[i], a[i - 1]);
}

void Sorting::run_sort(std::function<void(int *, int)> sort_func, const int *origin_arr, const int &n)
{
	int *sort_arr = new int[n];
	std::copy(origin_arr, origin_arr + n, sort_arr);

	sort_func(sort_arr, n);

	delete[] sort_arr;
}

void Sorting::print(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << a[i] << (i + 1 == n ? "\n" : ", ");
	}
}

Sorting::~Sorting() {}

int main(int argc, char *argv[])
{
	CommandLine cml;
	CommandArgs commandArgs = cml.parser(argc, argv);

	int *origin_arr = nullptr;
	int n = 0;

	cml.init_arr(origin_arr, commandArgs.random_size, n);

	Sorting sort(commandArgs.debug);

	RUN_SORT(sort, bubble_sort, origin_arr, n);
	RUN_SORT(sort, selection_sort, origin_arr, n);
	RUN_SORT(sort, insertion_sort, origin_arr, n);

	if (!commandArgs.not_do_print)
	{
		sort.print(origin_arr, n);
	}

	delete[] origin_arr;

	return 0;
}
