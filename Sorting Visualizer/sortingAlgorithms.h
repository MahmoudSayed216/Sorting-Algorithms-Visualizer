#pragma once
#include"columns.h"
#include<vector>
#include"columns.h"
class sortingAlgorithms
{
public: 
	static void initiateBubbleSort(std::vector<column>&);
	static void initiateMergeSort(std::vector<column>&);
	static void initiateSelectionSort(std::vector<column>&);

private:
	static void MergeSort();
	static void Merge();

};

