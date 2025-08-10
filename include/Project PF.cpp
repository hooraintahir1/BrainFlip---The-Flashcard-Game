#include <iostream>
#include<fstream>
#include <cstring>
#include <cstdlib> 
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

const int TOTAL = 5;

// Function to shuffle the questions every time the program runs
void shuffle(int order[], int size) {
    for (int i = 0; i < size; i++)
        order[i] = i;
    for (int i = 0; i < size; i++) {
        int r = rand() % size;
        int temp = order[i];
        order[i] = order[r];
        order[r] = temp;
    }
}

int level1() {
    char questions[TOTAL][100] = {
        "I am the capital of India, home to Red Fort and India Gate. What city am I?",
        "I go around the Earth and light up the night. What am I?",
        "I have a big clock tower, red buses, and the Queen used to live here. What city am I?",
        "I am a famous building and made of marble. People call me a symbol of love. What am I?",
        "I was the first Prime Minister of India and often wore a rose on my coat. Who am I?"
    };

    char answers[TOTAL][100] = {
        "Delhi",
        "Moon",
        "London",
        "Taj Mahal",
        "Nehru"
    };

    char userAnswer[100];
    int score = 0;
    int lives = 3;
    int order[TOTAL];

    shuffle(order, TOTAL);

    cout << "=== LEVEL 1 ===" << endl;
    Sleep(1000);
    cout << "\nLives: " << lives << endl;
    Sleep(1000);

    for (int i = 0; i < TOTAL && lives > 0; i++) {
        int index = order[i];

        cout << "\nQ" << (i + 1) << ": " << questions[index] << endl;
        cout << "Your answer: ";
        cin.getline(userAnswer, 100);

        if (strcmp(userAnswer, answers[index]) == 0) { //compares the user's answer with the correct answer
            cout << "Correct!" << endl;
            score++;
        }
        else {
            cout << "Wrong X - Correct answer: " << answers[index] << endl;
            lives--;
            cout << "Lives left: " << lives << endl;
        }
        Sleep(1000);
    }

    if (lives == 0) {
        cout << "Game Over! You ran out of lives!" << endl;
        exit(0);
    }
    else {
        cout << "\nLevel 1 complete!" << endl;
        cout << "\nYour final score: " << score << "/" << TOTAL << endl;

        cout << "Press SPACE BAR to continue to Level 2..." << endl;

        // if space bar is pressed then the level screen vanishes and level 2 screen appears
        while (true) { 
            if (_getch() == 32) break;
        }

        system("CLS");
    }
    return score;
}

int level2() {
    char questions[TOTAL][100] = {
        "Which planet is known as the Red Planet?",
        "What is the longest river in the world?",
        "Which city became the capital of Pakistan after independence?",
        "Which country was Hitler the leader of during World War II?",
        "How many continents are there in the world?"
    };

    char answers[TOTAL][100] = {
        "Mars",
        "Nile",
        "Karachi",
        "Germany",
        "7"
    };

    char hints[TOTAL][100] = {
        "It's the 4th planet from the Sun.",
        "It flows through Egypt.",
        "It was a major port city.",
        "It is known for Berlin.",
        "Less than 10, more than 5."
    };

    char userAnswer[100];
    int score = 0;
    int lives = 3;
    int order[TOTAL];
    int hintCount = 2;

    shuffle(order, TOTAL);

    cout << "\n=== LEVEL 2 ===" << endl;
    cout << "NOTE: You can use up to 2 hints by typing 'hint'and a timer of 10s." << endl;
    cout << "\nLives: " << lives << endl;
    Sleep(1500);

    for (int i = 0; i < TOTAL && lives > 0; i++) {
        int index = order[i];

        cout << "\nQ" << (i + 1) << ": " << questions[index] << endl;
        cout << "Your answer: ";

        time_t start = time(0);
        cin.getline(userAnswer, 100);
        time_t end = time(0);
        
        // check if user took more than 10 seconds to answer
        if (difftime(end, start) > 10) {
            cout << "Time's up!" << endl;
            lives--;
            cout << "Lives left: " << lives << endl;
            Sleep(1000);
            continue;
        }

        if (strcmp(userAnswer, "hint") == 0) {
            if (hintCount > 0) {
                cout << "Hint: " << hints[index] << endl;
                hintCount--;
                Sleep(1000);
                i--; // repeats the same question
                continue;
            }
            else {
                cout << "You have no hints left!" << endl;
                Sleep(1000);
                i--;
                continue;
            }
        }

        if (strcmp(userAnswer, answers[index]) == 0) {
            cout << "Correct!" << endl;
            score++;
        }
        else {
            cout << "Wrong X - Correct answer: " << answers[index] << endl;
            lives--;
            cout << "Lives left: " << lives << endl;
        }
        Sleep(1000);
    }

    if (lives == 0) {
        cout << "Game Over! You ran out of lives." << endl;
        exit(0);
    }
    else {
        cout << "\nCongratulations! You completed Level 2." << endl;
       // Sleep(1000);
        cout << "\nLevel 2 score: " << score << "/" << TOTAL << endl;
    }
    
    return score;
}

void saveScore(const char* name, int score) {
    ofstream file("leaderboard.txt", ios::app); // Opens the file in append mode to add new scores at the end
    if (file.is_open()) {
        file << name << " " << score << endl;
        file.close();
    }
}

void showLeaderboard() {
    ifstream file("leaderboard.txt");

    char names[100][100];
    int scores[100];
    int count = 0;

    // reads names and scores from the file
    while (file >> names[count] >> scores[count]) {
        count++;
    }
    file.close();

    // sorts the score in descending order using bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (scores[j] < scores[j + 1]) {

                int tempScore = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = tempScore;

                char tempName[100];
                strcpy_s(tempName, names[j]);
                strcpy_s(names[j], names[j + 1]);
                strcpy_s(names[j + 1], tempName);
            }
        }
    }

    cout << "\n=== LEADERBOARD ===" << endl;
    int displayCount;
    if (count < 5) {
        displayCount = count;
    }
    else {
        displayCount = 5; // shows only top 5
    }

    for (int i = 0; i < displayCount; i++) {
        cout << i + 1 << ". " << names[i] << " - " << scores[i] << endl;
    }
    cout << "====================" << endl;
}

int main() {
    srand(time(0)); // random using current time
    cout << "Welcome to BrainFlip: The Flashcard Game!" << endl;

    char playerName[100];
    cout << "Enter your name: ";
    cin.getline(playerName, 100);

    int totalScore = 0;

    totalScore += level1(); // calls level 1 and adds its score to total
    totalScore += level2();

    saveScore(playerName, totalScore);
    showLeaderboard();

    return 0;
}
