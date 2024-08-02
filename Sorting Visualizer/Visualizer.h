#pragma once
#include "columns.h"
#include "text.h"
#include "utils.h"
#include<vector>
#include <chrono>
#include <initializer_list>
#include<cstdlib>
#include<ctime>
#include<iostream>
#include <thread>
#include<functional>
#include<string>
class Visualizer
{
public:
	//attributes
	int screen_width;
	int screen_height;
	bool start_sorting;
	uint64_t recursive_calls;
	uint64_t comparisons;
	bool swapping_algorithm;	// this algorithm can utilize the swap functions [if so, it saves us the time of using "change_to_actual_position" function]
	std::vector<column> columns; 
	int numberOfColumns;
	int sleep_time = 0;
	sf::RenderWindow* window;
	int col_width;
	int numOfAlgos;
	uint16_t numberOfColors;
	TextEntity* algorithmName;
	TextEntity *instructions;
	TextEntity* comparisonsText;
	TextEntity* recCallsText;
	TextEntity* numberOfColumnsText;
	TextEntity* timeDelayText;
	uint16_t algoIndex;
	uint16_t colorSchemeIndex;
	std::vector<std::function<void()>> sortingAlgorithms;  // Change the type
	std::vector<std::string> algorithmsNames;
	std::vector<std::vector<sf::Color>> colorsSchemes;
	
	int recursionTracker;
	//methods
	Visualizer(int, int, int);
	void initializeTexts();
	void initializeColors();
	void create_random_set(bool);
	void check4events();
	void draw();
	void run();
	void initiateBubbleSort();
	void initiateMergeSort();
	void initiateInsertionSort();
	void initiateQuickSort();
	void change_to_actual_positions();
	void merge(int, int, int);
	void visualize_changes(std::initializer_list<int> indexes);
	void mergeSort(int, int);
	void insertionSort();
	void quickSort(int l, int r);
	int partition(int l, int r);
	void push_algos();
	void _sort();
	void set_columns_colors();
	~Visualizer();

};

