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
Font bloodyFont("Fonts/BLOODY.ttf");
Font write("Fonts/simple.ttf");

class Login{ //------LOGIN PAGE----//
    public:
       Login(){
            Texture loginTexture;
            if (!loginTexture.loadFromFile("Images/cover.png")) {
            cerr << "Error loading login texture!" << endl;
            }
            loginTexture.setSmooth(true);
            Sprite loginSprite(loginTexture);

            Text username(bloodyFont, "Username: ", 20);
            Text inputText(write, "", 20);
            Text backButton(bloodyFont,"back",20);
            backButton.setFillColor(Color::Black);
            backButton.setPosition({180.f,260.f});

            Text submitButton(bloodyFont,"submit",20);
            submitButton.setFillColor(Color::Black);
            submitButton.setPosition({540.f,260.f});

            CircleShape page(170.f);
            page.setPosition({60.f,50.f});
            page.setScale({2.f,1.f});
            page.setFillColor(Color(30,30,30,200));
            RectangleShape textField(Vector2f({ 300.f, 30.f }));
            Text title(bloodyFont,"Login",50);   //Log in title 
            title.setFillColor(Color(139,0,0));
            title.setPosition({300.f,60.f});
            title.setOutlineColor(Color::Black);
            title.setOutlineThickness(2.5f);
    }
};   