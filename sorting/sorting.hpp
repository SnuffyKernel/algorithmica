#ifndef SORTING_HPP
#define SORTING_HPP

#include <functional>
#include <mutex>

#include "command_line.hpp"

#define TIMER() Timer timer(__func__, debug)

#define RUN_SORT(sorter, method, data, size) \
	(sorter).tread_run_sort([&sorter](int *a, int n) { (sorter).method(a, n); }, (data), (size))

#define THREAD_RUN(name_thread, sorter, sort_method, arr, size) \
	std::thread name_thread([&sorter, arr, size]() { \
		RUN_SORT(sorter, sort_method, arr, size); \
	})

class Timer
{
private:
	static std::mutex cout_mutex;
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	std::string func_name;
	bool debug;

public:
	Timer(const std::string &name, const bool &_debug);
	~Timer();
};

class Sorting
{
private:
	static std::mutex cout_mutex;
	bool debug;

public:
	Sorting(const bool &_debug = false);

	void bubble_sort(int *a, int n);

	void selection_sort(int *a, int n);

	void insertion_sort(int *a, int n);

	void heapify(int* a, int n, int i);
	void heap_sort(int *a, int n);

	int relative_support_element(int *a,int low, int high);
	void quick_sort_recurs(int *a, int low, int high);
	void quick_sort(int *a, int n);

	void std_sort(int *a, int n);

	void tread_run_sort(std::function<void(int *, int)> sort_func, int *origin_arr, const int &n);
	void thread_run_all_sort(Sorting &sort, int *origin_arr, const int &size);

	void print(int *a, int n);

	~Sorting();
};

#endif // SORTING_HPP