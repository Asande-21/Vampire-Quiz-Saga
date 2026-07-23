#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

//Namespaces
using namespace sf;
using namespace std;



class  Sounds{
    //Import all songs  
    Sound setBuffer(string sound){
        SoundBuffer buffer(sound);
        return Sound(buffer);
    } 
    Sound background=setBuffer("Sounds/background.mp3");
    Sound stage2=setBuffer("Sounds/chapter2.mp3");
    Sound tuff=setBuffer("Sounds/vampire.mp3");
    Sound stage1=setBuffer("Sounds/chapter2.mp3");
    Sound timeUp=setBuffer("Sounds/timeUp.mp3");

    //Setting when to play sounds 
    //Must find a way to track the state of the game, must create a friend class
    
};
