#include "Visualizer.h"



Visualizer::Visualizer(int screen_width, int screen_height, int numOfCols)
{

	this->numberOfColumns = numOfCols;
	this->screen_height = screen_height;
	this->screen_width  = screen_width;
	this->comparisons = 0;
	this->recursive_calls = 0;
	algoIndex = 0;
	srand(std::time(0));
	colorSchemeIndex = 0;
	this->push_algos();
	this->recursionTracker = 0;
	this->window = new sf::RenderWindow(sf::VideoMode(screen_width, screen_height), "Soritng Algorithms Visualizer", sf::Style::Default);
	this->sleep_time = 0;
	this->col_width = screen_width/numOfCols;
	this->start_sorting = false;
	this->swapping_algorithm = false;
	this->numOfAlgos = 4;
	this->numberOfColors = 4;
	this->initializeColors();
	this->create_random_set(false);
	this->initializeTexts();
	

}

void Visualizer::initializeTexts()
{
	std::string algo_str = "Current Algorithm: " + algorithmsNames[algoIndex];
	this->algorithmName = new TextEntity(
		algo_str,
		"C:/Users/mahmo/Desktop/Code/C++/Sorting Visualizer/mister_saefudin/NunitoSans-Italic-VariableFont_YTLC,opsz,wdth,wght.ttf",
		37, sf::Color::Color(100, 230, 40), 650, 30
	);

	std::string inst_str = "A- Previous Algorithm\t      D- Next Algorithm\nE- Add 20 More Columns\tQ- Remove 20 Columns\nR- Generate a Random List\nC- Generate a Descending List\nSpace- Start Sorting\nTab- Change Color\n";
	this->instructions = new TextEntity(
		inst_str,
		"C:/Users/mahmo/Desktop/Code/C++/Sorting Visualizer/mister_saefudin/NunitoSans-Italic-VariableFont_YTLC,opsz,wdth,wght.ttf",
		25, sf::Color::White, 50, 30
	);

	std::string comp_str = "Comparisons: 0";
	this->comparisonsText = new TextEntity(
		comp_str,
		"C:/Users/mahmo/Desktop/Code/C++/Sorting Visualizer/mister_saefudin/NunitoSans-Italic-VariableFont_YTLC,opsz,wdth,wght.ttf",
		24, sf::Color::White, 1500, 30
	);

	std::string rec_calls_str = "Recursive calls: 0";
	this->recCallsText = new TextEntity(
		rec_calls_str,
		"C:/Users/mahmo/Desktop/Code/C++/Sorting Visualizer/mister_saefudin/NunitoSans-Italic-VariableFont_YTLC,opsz,wdth,wght.ttf",
		24, sf::Color::White, 1500, 70
	);

	std::string num_of_cols = "Number of Columns: " + std::to_string(this->numberOfColumns);
	this->numberOfColumnsText = new TextEntity(
		num_of_cols,
		"C:/Users/mahmo/Desktop/Code/C++/Sorting Visualizer/mister_saefudin/NunitoSans-Italic-VariableFont_YTLC,opsz,wdth,wght.ttf",
		24, sf::Color::White, 1500, 110
	);

	std::string delay_in_ms= "Delay: " + std::to_string(this->sleep_time) + " ms";
	this->timeDelayText = new TextEntity(
		delay_in_ms,
		"C:/Users/mahmo/Desktop/Code/C++/Sorting Visualizer/mister_saefudin/NunitoSans-Italic-VariableFont_YTLC,opsz,wdth,wght.ttf",
		24, sf::Color::White, 1500, 150
	);

}

void Visualizer::initializeColors()
{
	std::vector<sf::Color> red   = { sf::Color::Color(250,200, 200), sf::Color::Color(250, 150, 150),sf::Color::Color(250,90,90) };
	std::vector<sf::Color> blue  = { sf::Color::Color(200,250, 200), sf::Color::Color(150, 250, 150),sf::Color::Color(90,250,90) };
	std::vector<sf::Color> green = { sf::Color::Color(0,130, 250), sf::Color::Color(0, 170, 250),sf::Color::Color(0,210,250) };
	std::vector<sf::Color> gray = { sf::Color::Color(85, 85, 85), sf::Color::Color(220, 220, 220), sf::Color::Color(150, 150, 150) };

	this->colorsSchemes.push_back(gray);
	this->colorsSchemes.push_back(red);
	this->colorsSchemes.push_back(blue);
	this->colorsSchemes.push_back(green);

}

void Visualizer::create_random_set(bool descending =  false)
{
	this->columns.clear();
	int x_pos = 0;
	this->columns.clear();
	std::vector<sf::Color> colors = this->colorsSchemes[this->colorSchemeIndex];
	std::vector<int> randomNumbers;
	for (int i = 0; i < this->numberOfColumns; i++) {
		int random_height = std::rand() % 900;
		randomNumbers.push_back(random_height);
	}

	if (descending) std::sort(randomNumbers.begin(), randomNumbers.end(), std::greater<>());

	for (int i = 0; i < numberOfColumns; i++) {
		column col(col_width, randomNumbers[i], x_pos, this->screen_height);
		x_pos = x_pos + col_width;
		this->columns.push_back(col);
	}
	this->set_columns_colors();
}

void Visualizer::check4events()
{
	sf::Event event;

	while (window->pollEvent(event)) {
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
		case sf::Event::KeyPressed: {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				std::cout << "Space was pressed" << std::endl;
				start_sorting = !start_sorting;
				if (start_sorting) {
					_sort();
				}
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				std::cout << "D was pressed" << std::endl;
				algoIndex == this->numOfAlgos - 1 ? algoIndex = 0 : algoIndex++;
				this->algorithmName->setString("Current Algorithm: " + algorithmsNames[this->algoIndex]);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				std::cout << "A was pressed" << std::endl;
				algoIndex == 0 ? algoIndex = this->numOfAlgos-1 : algoIndex--;
				this->algorithmName->setString("Current Algorithm: " + algorithmsNames[this->algoIndex]);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				std::cout << "R was pressed" << std::endl;
				this->create_random_set(false);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				std::cout << "C was pressed" << std::endl;
				this->create_random_set(true);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
				std::cout << "Tab was pressed" << std::endl;
				colorSchemeIndex = (colorSchemeIndex + 1) % numberOfColors;
				this->set_columns_colors();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				this->numberOfColumns += 20;
				if (this->numberOfColumns > 900)
					this->numberOfColumns = 900;
				this->col_width = screen_width / this->numberOfColumns;
				this->numberOfColumnsText->setString("Number of Columns: " + std::to_string(numberOfColumns));
				this->create_random_set();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				this->numberOfColumns -= 20;
				if (numberOfColumns < 2)
					numberOfColumns = 2;
				this->col_width = screen_width / this->numberOfColumns;
				this->numberOfColumnsText->setString("Number of Columns: " + std::to_string(numberOfColumns));
				this->create_random_set();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
				this->sleep_time += 1;
				this->timeDelayText->setString("Delay: " + std::to_string(sleep_time) + " ms");
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
				this->sleep_time -= 1;
				if (this->sleep_time < 0)
					this->sleep_time = 0;
				this->timeDelayText->setString("Delay: " + std::to_string(sleep_time) + " ms");

			}
		}
		default:
			break;
		}
	}

}

void Visualizer::draw()
{
	window->clear(sf::Color::Color(50, 50, 50));
	for (column &c : this->columns) {
		c.draw_on_screen(window);
	}
	algorithmName->draw_on_screen(this->window);
	instructions->draw_on_screen(this->window);
	comparisonsText->draw_on_screen(this->window);
	recCallsText->draw_on_screen(this->window);
	numberOfColumnsText->draw_on_screen(this->window);
	timeDelayText->draw_on_screen(this->window);
	window->display();
}

void Visualizer::run()
{
	while (window->isOpen()) {
		this->check4events();
		this->draw();
	}
}

void Visualizer::initiateBubbleSort()
{
	bool a_swap_has_occured = false;
	this->swapping_algorithm = true;
	int size = columns.size();
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size - i; j++) {
			if (columns[j].get_height() > columns[j + 1].get_height()) {
				comparisons++;
				column::swap(columns[j], columns[j + 1]);
				a_swap_has_occured = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
				visualize_changes({ j });
			}
		}
		if (!a_swap_has_occured)
			break;
		a_swap_has_occured = false;

	}

	start_sorting = false;
}

void Visualizer::initiateMergeSort()
{
	this->swapping_algorithm = false;
	int l = 0;
	int r = this->numberOfColumns-1;
	mergeSort(l, r);
	this->start_sorting = false;
}


void Visualizer::initiateInsertionSort()
{
	this->swapping_algorithm = true;
	insertionSort();
	this->start_sorting = false;
}

void Visualizer::initiateQuickSort()
{
	this->swapping_algorithm = true;
	quickSort(0, this->numberOfColumns-1);
	this->start_sorting = false;
}

void Visualizer::quickSort(int l, int r)
{
	int index = partition(l, r);

	if (l < r - 1)
		recursive_calls++, quickSort(l, index - 1);

	if (index < r)
		recursive_calls++, quickSort(index, r);
}

int Visualizer::partition(int l, int r)
{
	int i = l, j = r;
	int pivot = columns[(l + r) / 2].get_height();

	while (i <= j) {
		while (columns[i].get_height() < pivot)
			i++, comparisons++;

		while (columns[j].get_height() > pivot)
			j--, comparisons++;

		if (i <= j) {
			column::swap(columns[i], columns[j]);
			std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
			visualize_changes({i, j});
			
			i++;
			j--;
		}

	};

	return i;
}


void Visualizer::insertionSort()
{

	for (int i = 1; i < this->numberOfColumns; i++) {
		column key = columns[i];
		int j;
		for (j = i - 1; j >= 0; j--) {
			if (key.get_height() < columns[j].get_height()) {
				comparisons++;
				column::swap(columns[j + 1], columns[j]);
				std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
				this->visualize_changes({ j });
			}
			else {
				break;
			}
		}
		columns[j + 1] = key;

	}
}




void Visualizer::change_to_actual_positions()
{
	int size = this->columns.size();
	int start_pos = 0;
	for (int i = 0; i < size; i++) {
		columns[i].unit->setPosition(start_pos, screen_height);
		start_pos += this->col_width;
	}
}

void Visualizer::merge(int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;

	std::vector<column> leftArr(n1);
	std::vector<column> rightArr(n2);

	for (int i = 0; i < n1; ++i)
		leftArr[i] = columns[left + i];
	for (int j = 0; j < n2; ++j)
		rightArr[j] = columns[mid + 1 + j];
	utils::print_array(leftArr);
	utils::print_array(rightArr);
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (leftArr[i].get_height() <= rightArr[j].get_height()) {
			columns[k]= leftArr[i];
			i++;
		}
		else {
			columns[k] = rightArr[j];
			j++;
			
		}
		comparisons++;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		visualize_changes({ k });
		k++;
	}

	while (i < n1) {
		columns[k] = leftArr[i];
		i++;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		visualize_changes({ k });
		k++;
	}

	while (j < n2) {
		columns[k] = rightArr[j];
		j++;
		std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
		visualize_changes({ k });
		k++;
	}
}

void Visualizer::visualize_changes(std::initializer_list<int> indexes)
{

	if(!this->swapping_algorithm)
		this->change_to_actual_positions();
	std::vector<sf::Color> temp;
	int i = 0;
	for (int index : indexes) {
		i++;
		temp.push_back(columns[index].unit->getFillColor());
		columns[index].unit->setFillColor(sf::Color::Red);
	}
	
	this->comparisonsText->setString("Comparisons: " + std::to_string(comparisons));
	this->recCallsText->setString("Recursive Calls: " + std::to_string(recursive_calls));

	draw();

	for (int index : indexes) {
		columns[index].unit->setFillColor(temp[--i]);
	}
}

void Visualizer::mergeSort(int left, int right)
{
	start_sorting = false;
	if (left < right) {
		int mid = left + (right - left) / 2;
		this->recursionTracker+=2;
		recursive_calls += 2;
		mergeSort(left, mid);
		mergeSort(mid + 1, right);
		
		this->recursionTracker -= 2;
		merge(left, mid, right);
		if (!recursionTracker) {
			utils::print_array(this->columns);
		}
		
	}
}


void Visualizer::push_algos()
{
	// pushing the algorithms
	this->sortingAlgorithms.push_back(std::bind(&Visualizer::initiateBubbleSort, this));
	this->sortingAlgorithms.push_back(std::bind(&Visualizer::initiateMergeSort, this));
	this->sortingAlgorithms.push_back(std::bind(&Visualizer::initiateInsertionSort, this));
	this->sortingAlgorithms.push_back(std::bind(&Visualizer::initiateQuickSort, this));


	// pushing their names for display
	this->algorithmsNames.push_back("Bubble Sort");
	this->algorithmsNames.push_back("Merge Sort");
	this->algorithmsNames.push_back("Insertion Sort");
	this->algorithmsNames.push_back("Quick Sort");
}

void Visualizer::_sort()
{
	comparisons = 0;
	recursive_calls = 0;
	int size = this->columns.size();
	sortingAlgorithms[algoIndex]();

	//the following function was replaced with a better logic within the column::swap function, 
	//im just keeping it in case i needed it in another context
	//change_to_actual_positions();

}

void Visualizer::set_columns_colors()
{
	std::vector<sf::Color> colorScheme = colorsSchemes[this->colorSchemeIndex];

	for (column& c : this->columns) {
		uint16_t _rand_index = (uint16_t)rand() % 3;
		c.unit->setFillColor(colorScheme[_rand_index]);
	}
}



Visualizer::~Visualizer()
{
	delete window;
	int size = this->columns.size();
	for (int i = 0; i < size; i++) {
		delete columns[i].unit;
	}
	delete algorithmName;
	delete instructions;
	delete comparisonsText;
	delete recCallsText;
	delete numberOfColumnsText;
	delete timeDelayText;
}
