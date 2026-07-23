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
using namespace sf;
using namespace std;


class Base{
    public:
      //Fonts of the game .
      friend class Login;
      Font nightcoreFont("Fonts/Nightcore Demo.ttf");
      Font bloodyFont("Fonts/BLOODY.ttf");
      Font font2("Fonts/crimes.ttf");
      Font font3("Fonts/Stranger back in the Night.ttf");
      Font write("Fonts/simple.ttf");
      Font write1("Fonts/Another Danger - Demo.otf");
};
