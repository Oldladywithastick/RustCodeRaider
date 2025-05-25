#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<string> load_numbers(const string &filename) { //load numbers into vector 
    ifstream file(filename);
    vector<string> numbers;
    string num_str;
    while (file >> num_str) {
        numbers.push_back(num_str);
    }
    return numbers;
}

void save_Progress(int i, const string &filename) { //create new file to save progress
    ofstream file(filename);
    file << i;
}

int loadProgress(const string &filename) { //load progress from last time
    ifstream file(filename);
    int index = 0;
    if (file >> index) {
        return index;
    }
    return 0;
}

int main() {
    vector<string> numbers = load_numbers("numbers.txt"); //load numbers into vector from file
    if (numbers.empty()) {
        cout << "numbers.txt not found or empty." << endl;
        return 1;
    }

    int index = loadProgress("progress.txt"); //set index to last saved progress

    sf::RenderWindow window(sf::VideoMode(400, 200), "Rust Code Raider"); //create window
    sf::Font font; 
    if (!font.loadFromFile("Vogue.ttf")) {
        cout << "Font could not be loaded\n";
        return 1;
    }

    sf::Text text;  //set text properties
    text.setFont(font);
    text.setCharacterSize(40);
    text.setFillColor(sf::Color(200, 200, 200));
    text.setOutlineColor(sf::Color::Black);

    sf::Text progress_text; //set progress
    progress_text.setFont(font);
    progress_text.setCharacterSize(20);
    progress_text.setFillColor(sf::Color(200, 200, 200));
    progress_text.setOutlineColor(sf::Color::Black);
    
    sf::Text input_prompt; //set input_prompt properties
    input_prompt.setFont(font);
    input_prompt.setCharacterSize(25);
    input_prompt.setFillColor(sf::Color(200, 200, 200));
    input_prompt.setOutlineColor(sf::Color::Black);
    
    std::string inputString;
    bool inputMode = false; //currently in input mode 

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event))  //Events 
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
            {
                save_Progress(index, "progress.txt");
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) 
            {
                if (inputMode == true) 
                {
                    if (event.key.code == sf::Keyboard::Enter)  //logic for line switching 
                    {
                        int lineNum = std::stoi(inputString);
                        if (lineNum >= 1 && lineNum <= numbers.size()) 
                        {
                            index = lineNum - 1;
                        } 
                        else 
                        {
                            cout << "Invalid line number.\n";
                        }
                        inputString.clear();
                        inputMode = false;
                    }
                    else if (event.key.code == sf::Keyboard::Backspace && !inputString.empty()) 
                    {
                        inputString.pop_back();
                    }
                    else if (event.key.code == sf::Keyboard::Escape) 
                    {
                        inputString.clear();
                        inputMode = false;
                    }
                } 
                else 
                {
                    if (event.key.code == sf::Keyboard::Right && index < numbers.size() - 1) 
                    {
                        index++;
                    }
                    else if (event.key.code == sf::Keyboard::Left && index > 0) 
                    {
                        index--;
                    }
                    else if (event.key.code == sf::Keyboard::J) 
                    {
                        inputMode = true;
                        inputString.clear();
                    }
                }
            }
            else if (event.type == sf::Event::TextEntered && inputMode) 
            {
                if (event.text.unicode >= '0' && event.text.unicode <= '9') 
                {
                    inputString += static_cast<char>(event.text.unicode);
                }
            }
        }
        text.setString("Number: " + numbers[index]); //display current number
        //centralize text in the upper part of the window
        sf::FloatRect bounds = text.getLocalBounds(); 
        text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
        text.setPosition(window.getSize().x / 2.f, window.getSize().y / 4.f);
        //Progress counter, centralized in the middle of the window
        progress_text.setString("Progress: " + to_string(index + 1) + " / " + to_string(numbers.size()));
        sf::FloatRect progBounds = progress_text.getLocalBounds();
        progress_text.setOrigin(progBounds.left + progBounds.width / 2.f, progBounds.top + progBounds.height / 2.f);
        progress_text.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);
        //display input prompt
        if (inputMode) {
            input_prompt.setString("Jump to line: " + inputString + "_");
        } else {
            input_prompt.setString("Press J to jump to a line");
        }
        //centralize in lower part of the window
        sf::FloatRect promptBounds = input_prompt.getLocalBounds();
        input_prompt.setOrigin(promptBounds.left + promptBounds.width / 2.f, promptBounds.top + promptBounds.height / 2.f);
        input_prompt.setPosition(window.getSize().x / 2.f, 3 * window.getSize().y / 4.f);
        //draw window
        window.clear(sf::Color(16, 24, 32));
        window.draw(text);
        window.draw(progress_text);
        window.draw(input_prompt);
        window.display();
    }

    return 0;
}
