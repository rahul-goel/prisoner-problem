#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <numeric>
#include <algorithm>
#include <iomanip>

std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());

std::vector<int> assign_boxes(int n) {
	std::vector<int> boxes(n);
	std::iota(boxes.begin(), boxes.end(), 0);
	std::shuffle(boxes.begin(), boxes.end(), rng);
	return boxes;
}

bool prisoner_simulate(std::vector<int> &boxes, int prisoner_id, int num_box_open) {
	int box_id = prisoner_id;
	bool found = false;
	for (int i = 0; i < num_box_open; ++i) {
		if (boxes[box_id] == prisoner_id) {
			found = true;
			break;
		}
		box_id = boxes[box_id];
	}
	return found;
}

bool simulate_experiment(int num_prisoners, int num_box_open) {
	std::vector<int> boxes = assign_boxes(num_prisoners);
	bool success = true;
	for (int i = 0; i < num_prisoners; ++i) {
		success = success and prisoner_simulate(boxes, i, num_box_open);
	}
	return success;
}

int main(int argc, char *argv[]) {
	int num_simulations = std::atoi(argv[1]);
	int num_prisoners = std::atoi(argv[2]);
	int num_box_open = std::atoi(argv[3]);

	long double success_exp = 0;
	for (int i = 0; i < num_simulations; ++i) {
		success_exp += simulate_experiment(num_prisoners, num_box_open);
	}

	long double probability = success_exp / num_simulations;

	std::cout << std::fixed << std::setprecision(6) << probability << std::endl;
	return 0;
}
