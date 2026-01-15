#include <iostream>
#include <chrono>
#include <functional>
#include <thread>

#include "sorting.hpp"

std::mutex Timer::cout_mutex;

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

		std::lock_guard<std::mutex> lock(cout_mutex);
		std::cout << func_name << " took: " << duration.count() << " microsec";
		std::cout << " (" << duration.count() / 1000.0 << " ms)\n";
	}
}

std::mutex Sorting::cout_mutex;

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
	{
		for (int j = k + 1; j < n; j++)
		{
			if (a[k] > a[j])
			{
				Utils::swap(a[j], a[k]);
			}
		}
	}
}

void Sorting::insertion_sort(int *a, int n)
{
	TIMER();

	for (int k = 1; k < n; k++)
	{
		for (int i = k; i > 0 && a[i] < a[i - 1]; i--)
		{
			Utils::swap(a[i], a[i - 1]);
		}
	}
}

void Sorting::heapify(int *a, int n, int i)
{
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && a[left] > a[largest])
		largest = left;

	if (right < n && a[right] > a[largest])
		largest = right;

	if (largest != i)
	{
		Utils::swap(a[i], a[largest]);

		heapify(a, n, largest);
	}
}

void Sorting::heap_sort(int *a, int n)
{
	TIMER();

	for (int i = n / 2 - 1; i >= 0; i--)
	{
		heapify(a, n, i);
	}

	for (int i = n - 1; i > 0; i--)
	{
		std::swap(a[0], a[i]);

		heapify(a, i, 0);
	}
}

void Sorting::run_sort(std::function<void(int *, int)> sort_func, const int *origin_arr, const int &n)
{
	int *sort_arr = new int[n];

	std::unique_lock<std::mutex> lock(cout_mutex);
	std::copy(origin_arr, origin_arr + n, sort_arr);
	lock.unlock();

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

void run_all_func_thread(Sorting &sort, int *origin_arr, const int &size)
{
	typedef void (Sorting::*SortMethodPtr)(int *, int);

	SortMethodPtr methods[] =
	{
		&Sorting::bubble_sort,
		&Sorting::selection_sort,
		&Sorting::insertion_sort,
		&Sorting::heap_sort
	};

	std::vector<std::thread> threads;

	for (size_t i = 0; i < sizeof(methods) / sizeof(methods[0]); i++)
	{
		threads.emplace_back([&sort, origin_arr, size, method = methods[i]]()
		{
			sort.run_sort([&sort, method](int *a, int n)
			{
				(sort.*method)(a, n);
			}, origin_arr, size);
		});
	}

	for (auto &t : threads)
	{
		t.join();
	}
}

int main(int argc, char *argv[])
{
	CommandLine cml;
	CommandArgs commandArgs = cml.parser(argc, argv);

	int *origin_arr = nullptr;
	int n = 0;

	cml.init_arr(origin_arr, commandArgs.random_size, n);

	Sorting sort(commandArgs.debug);

	run_all_func_thread(sort, origin_arr, n);

	//THREAD_RUN(t1, sort, bubble_sort, origin_arr, n);

	//t1.join();

	if (!commandArgs.not_do_print)
	{
		sort.print(origin_arr, n);
	}

	delete[] origin_arr;

	return 0;
}
