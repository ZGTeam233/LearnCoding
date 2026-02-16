#include <iostream>

// GOD, HOPE IT THIS CODE WORKS FINE NOW.

int main() {
    int guess = 0;
    int attempts = 0; // 猜测次数
    const int password[5] = { 42, 15, 7, 93, 28 }; // 猜数字游戏答案
    int round = 0; // 当前轮数
    int choice;
    std::cout << "Welcome to the Guessing Game!\n";
    std::cout << "I have selected a number between 1 and 100.\n";
    std::cout << "Can you guess what it is ?\n";
    std::cout << "You have seven attempts to guess the correct number.\n";
    while (guess != password[round]) {
        if (attempts < 7) {
            // 允许猜测
            std::cout << "Enter your guess: ";
            std::cin >> guess;
            attempts++;

            if (guess < password[round])
                std::cout << "Too low! Try again.\n"; // 猜测过低
            else if (guess > password[round])
                std::cout << "Too high! Try again.\n"; // 猜测过高
            else {
                // 猜测正确
                std::cout << "Congratulations! You've guessed the correct number: " << password[round] << ".\n" << std::endl;
                if (round == 4) {
                    // 完成所有轮次
                    std::cout << "You've completed all rounds! Well done!\n";
                    break;
                }
                else {
                    // 询问是否继续下一轮
                    std::cout << "Wanna try the next number? Input 1 to continue or 0 to quit: ";
                    std::cin >> choice;
                    if (choice == 1) {
                        // 继续下一轮
                        round++;
                        attempts = 0;
                        guess = 0;
                    }
                    else {
                        // 退出游戏
                        std::cout << "Thanks for playing! Goodbye!\n";
                        break;
                    }
                }
            }
        }
        else {
            // 超过七次未猜中
            std::cout << "Sorry, you've used all your attempts. The correct number was " << password[round] << ".\n" << std::endl;
            break;
        }
    }
    return 0;
}