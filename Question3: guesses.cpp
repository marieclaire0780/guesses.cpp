#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

string choose_random_word() {
    // List of words for the game (you can add more if you want)
    vector<string> word_list = {"hangman", "cpp", "programming", "computer", "science", "knowledge", "challenge"};

    // Choose a random word from the list
    random_device rd;
    mt19937 gen(rd());
    shuffle(word_list.begin(), word_list.end(), gen);
    return word_list[0];
}

string display_word(const string& word, const vector<char>& guessed_letters) {
    // Display the word with letters already guessed shown and others as '-'
    string displayed_word;
    for (char letter : word) {
        if (find(guessed_letters.begin(), guessed_letters.end(), letter) != guessed_letters.end()) {
            displayed_word += letter;
        } else {
            displayed_word += '-';
        }
    }
    return displayed_word;
}

bool is_valid_guess(char guess) {
    // Check if the input is a single alphabet letter
    return isalpha(guess);
}

bool is_vowel(char letter) {
    // Check if the letter is a vowel (a, e, i, o, u)
    letter = tolower(letter);
    return (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u');
}

void hangman_game() {
    string word = choose_random_word();
    vector<char> guessed_letters;
    vector<char> unique_letters(word.begin(), word.end());
    sort(unique_letters.begin(), unique_letters.end());
    unique_letters.erase(unique(unique_letters.begin(), unique_letters.end()), unique_letters.end());
    
    int warnings = 3;
    int guesses_left = 6;

    cout << "Welcome to Hangman!" << endl;
    cout << "The word has " << word.length() << " letters." << endl;

    while (guesses_left > 0) {
        cout << endl << "You have " << guesses_left << " guesses left." << endl;
        cout << "Available letters: ";
        for (char letter = 'a'; letter <= 'z'; ++letter) {
            if (find(guessed_letters.begin(), guessed_letters.end(), letter) == guessed_letters.end()) {
                cout << letter;
            }
        }
        cout << endl;

        char guess;
        cout << "Please guess a letter: ";
        cin >> guess;
        guess = tolower(guess);

        if (!is_valid_guess(guess)) {
            if (warnings > 0) {
                warnings--;
                cout << "Please enter a valid letter. You have " << warnings << " warnings left." << endl;
            } else {
                cout << "Please enter a valid letter. You have no warnings left." << endl;
                guesses_left--;
            }
        } else {
            if (find(guessed_letters.begin(), guessed_letters.end(), guess) != guessed_letters.end()) {
                if (warnings > 0) {
                    warnings--;
                    cout << "You've already guessed that letter. You have " << warnings << " warnings left." << endl;
                } else {
                    cout << "You've already guessed that letter. You have no warnings left." << endl;
                    guesses_left--;
                }
            } else {
                guessed_letters.push_back(guess);
                if (word.find(guess) != string::npos) {
                    cout << "Good guess: " << display_word(word, guessed_letters) << endl;
                } else {
                    if (is_vowel(guess)) {
                        guesses_left -= 2;
                    } else {
                        guesses_left--;
                    }
                    cout << "Oops! That letter is not in the word: " << display_word(word, guessed_letters) << endl;
                }
            }
        }

        if (display_word(word, guessed_letters) == word) {
            int score = guesses_left * unique_letters.size();
            cout << endl << "Congratulations, you guessed the word: " << word << endl;
            cout << "Your score: " << score << endl;
            return;
        }
    }

    cout << endl << "Sorry, you ran out of guesses. The word was: " << word << endl;
}

int main() {
    hangman_game();
    return 0;
}
