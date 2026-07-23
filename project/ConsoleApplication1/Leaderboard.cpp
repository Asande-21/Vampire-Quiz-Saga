#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
using namespace sf;
using namespace std;

struct Leaderboard{
    
    Text leaderBoardTitle(const sf::Font& font) {
        sf::Text text(font);
        text.setString("LeaderBoard");
        text.setCharacterSize(50);
        text.setPosition({ 550.f, 100.f });
        text.setFillColor(sf::Color::White);

        return text;
    }
    RectangleShape highlights(float x, float y) {
        RectangleShape shape;
        shape.setPosition({ x, y });
        shape.setFillColor(sf::Color(255, 255, 0, 100));
        shape.setSize({ 800.f, 30.f });
    
        return shape;
    }

    Text leaderboard(const Font& font, multimap<int, string, greater<>>& scores, const string& userName, int& score) {
        bool found = false;
        for (auto i = scores.begin(); i != scores.end(); ++i) {
            if (i->second == userName) {
                found = true;
                scores.erase(i);
                scores.insert({ score, userName });
                break;
            }
        }
        
        if (!found) {
            scores.insert({ score,userName });
        }
        
        
        stringstream ss;

        int i = 1;
        for (const auto& pair : scores) {
            ss << left << setw(2) << i << ". "
                << setw(30) << pair.second << "\t"
                << right << setw(4) << pair.first << "\n";
            
        }
        sf::Text text(font);
        text.setString(ss.str());
        text.setCharacterSize(30);
        text.setPosition({ 350.f, 200.f });
        text.setFillColor(sf::Color::White);

        return text;
    }

};