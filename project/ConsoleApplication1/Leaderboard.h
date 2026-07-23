#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <random>
using namespace sf;
using namespace std;
struct Leaderborad{
    
       Text leaderBoardTitle(const Font& font);
       RectangleShape highlights(float x, float y);
       Text leaderboard(const Font& font, multimap<int, string, greater<>>& scores, const string& userName, int& score);
       
};