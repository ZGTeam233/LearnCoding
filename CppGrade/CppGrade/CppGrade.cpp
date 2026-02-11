#include <iostream>

using namespace std;

int checkLevel() {
	int grade;
	std::cout << "Enter your grade (0-100): ";
	std::cin >> grade;
	if (grade > 100 || grade < 0) {
		std::cout << "Invalid grade. Please enter a number between 0 and 100.\n";
		return 1; // 带错误退出函数
	}
	switch (grade / 10) {
	case 10:
	case 9:
		std::cout << "Grade level: A, outstanding\n";
		break;
	case 8:
		std::cout << "Grade level: B, exceeded expectations\n";
		break;
	case 7:
		std::cout << "Grade level: C, accept\n";
		break;
	case 6:
		std::cout << "Grade level: D, poor\n";
		break;
	default:
		std::cout << "Grade level: E, dreadful\n";
		break;
	}
}

void checkScholarship() {

}

void showEvaluation() {

}

int main() {
	int choice;

	while (true) {
		cout << "\nPlease select an action to perform(enter a number 1 - 4):\n";
		cout << "1. Check grade level\n";
		cout << "2. Determine if scholarship is awarded\n"; // 判断是否获得奖学金
		cout << "3. Show this semester's evaluation\n"; // 显示本学期评价
		cout << "4. Exit program\n";
		cout << "Your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			checkLevel();
			break;
		case 2:
			checkScholarship();
			break;
		case 3:
			showEvaluation();
			break;
		case 4:
			cout << "Exiting program. Goodbye!\n";
			return 0;
		default:
			cout << "Invalid choice. Please enter a number between 1 and 4.\n";
			break;
		}
	}
}