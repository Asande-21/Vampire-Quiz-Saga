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

// --- GAME CONSTANTS --- //
const int STARTING_HP = 10;
const vector<string> STAGES = { "ACADEMY", "CITY", "CASTLE", "" };
const map<string, string> STAGE_WEAPONS = {
    {"ACADEMY", "SILVER DAGGER"},
    {"CITY", "HOLY WATER"},
    {"CASTLE", "WOODEN STAKE"}
};
const int QUESTIONS_PER_STAGE = 10;
const float QUESTION_TIME_LIMIT = 30.0f; 


// --- FONTS FIRST --- //
Font nightcoreFont("Fonts/Nightcore Demo.ttf");
Font bloodyFont("Fonts/BLOODY.ttf");
Font font2("Fonts/crimes.ttf");
Font font3("Fonts/Stranger back in the Night.ttf");
Font write("Fonts/simple.ttf");
Font write1("Fonts/Another Danger - Demo.otf");

// --- QUESTION STRUCT --- //
struct Question {
    string text;
    vector<string> options;
    char correctAnswer;
    bool isMultipleChoice;
    int id;
};

string IntroStoryLine="Genre: Gothic Horror / Quiz Adventure\nFormat: True or False & Multiple Choice\nChapters: Academy ->City -> Castle\n\n\nStory Overview::\nIn a world where the line between myth and reality is razor-thin, ancient bloodlines stir \nin the shadows. You are  a fledgling member of the Order of the Crimson Dawn and \nyou have been chosen to complete the sacred Vampire Trials a mental and mystical gauntlet \nthat tests knowledge,courage, and cunning.\n\nYour ultimate goal is to Defeat the legendary vampire overlord Vladric, whose awakening \nthreatens to plunge the world into eternal night.\nBut before you can confront him, you must first survive three terrifying trials...";
string chp1StoryLine="Difficulty: Novice\nTheme: Vampire Lore 101\n\nStory Time:\n\nYou begin your journey at the secretive Crimson Academy, a haunted \ninstitution hidden beneath the Carpathian mountains.\nHere, you're trained in vampire fundamentals—weaknesses, habits, and ancient \nsuperstitions. Through lessons passed down by dusty tomes and spectral tutors, you learn how to \nrecognize vampire signs, defend against their tricks, and prepare for what lies beyond.\n\nFocus Areas:\n\nVampire myths and facts\nCore weaknesses (sunlight, garlic, silver)\nTraditional vampire rules and behavior";
string chp2StoryLine="Difficulty: Intermediate\nTheme: Urban Vampirism\n\nStoryTime:\n\nGraduating from the Academy, you're deployed to a cursed metropolis under siege. \nThe city's fog-drenched streets conceal predators in human form—Urban Vampires \nwho blend into society. Your task: track these creatures, uncover their lairs, and \noutwit their evolving tactics before the city is lost to the night.\n\nFocus Areas:\n\nVampire tactics in modern settings\nDetection and hunting methods\nUrban legends vs. real threats";
string chp3StoryLine= "Difficulty: Advanced\nTheme: Vladric's Domain\n\nStory Time\n\nThe trail leads you to Castle Noctis, Vladric's ancestral fortress shrouded in eternal \nstorm clouds and dark enchantments. Here, you face horrors beyond mortal understanding: \nvampire lords, cursed relics, and Vladric himself—whose powers defy even ancient lore. \nOnly those with complete mastery of vampire knowledge and steely nerves can hope to \nsurvive the final confrontation.\n\nFocus Areas:\n\nAncient vampire powers\nVladric's personal lore and weaknesses\nRelic-based combat strategies";


// --- QUESTION BANK --- //
vector<Question> questionBank = {
    // ================== ACADEMY STAGE ================== //
    // Academy True/False Questions (8 questions)
    {"VAMPIRES CAN'T CROSS RUNNING WATER.", {}, 'T', false, 0},
    {"GARLIC PROTECTS AGAINST VAMPIRES.", {}, 'T', false, 1},
    {"VAMPIRES CAN TRANSFORM INTO WOLVES.", {}, 'T', false, 2},
    {"VAMPIRES CAST SHADOWS.", {}, 'F', false, 3},
    {"VAMPIRES MUST SLEEP IN THEIR NATIVE SOIL.", {}, 'T', false, 4},
    {"A VAMPIRE CAN ENTER ANY HOME UNINVITED.", {}, 'F', false, 5},
    {"VAMPIRES CAN CONTROL THE WEATHER.", {}, 'F', false, 6},
    {"SILVER CAN BURN A VAMPIRE'S SKIN.", {}, 'T', false, 7},

    // Academy Multiple Choice Questions (8 questions)
    {"WHAT KILLS VAMPIRES?", {"SUNLIGHT", "SILVER", "BOTH"}, 'C', true, 8},
    {"VAMPIRES CAN BE KILLED BY:", {"DECAPITATION", "FIRE", "BOTH"}, 'C', true, 9},
    {"VAMPIRES CAST:", {"SHADOWS", "REFLECTIONS", "NEITHER"}, 'C', true, 10},
    {"TO REPEL VAMPIRES, USE:", {"GARLIC", "HOLY SYMBOLS", "BOTH"}, 'C', true, 11},
    {"VAMPIRES ARE MOST ACTIVE DURING:", {"DAYLIGHT", "TWILIGHT", "NIGHT"}, 'C', true, 12},
    {"A VAMPIRE'S STRENGTH COMES FROM:", {"AGE", "BLOOD INTAKE", "BOTH"}, 'C', true, 13},
    {"VAMPIRES CAN BE DETECTED BY:", {"MIRRORS", "HOLY WATER", "BOTH"}, 'B', true, 14},
    {"THE MOST EFFECTIVE WOODEN STAKE IS MADE FROM:", {"OAK", "ASH", "HAWTHORN"}, 'C', true, 15},

    // ================== CITY STAGE ================== //
    // City True/False Questions (8 questions) - Harder
    {"VAMPIRES CAN ENTER HOMES WITHOUT INVITATION.", {}, 'F', false, 16},
    {"VAMPIRES ALWAYS SLEEP IN COFFINS.", {}, 'T', false, 17},
    {"VAMPIRES ARE HARMED BY RELIGIOUS SYMBOLS.", {}, 'T', false, 18},
    {"VAMPIRES CAN CLIMB WALLS LIKE SPIDERS.", {}, 'T', false, 19},
    {"URBAN VAMPIRES CAN BLEND IN WITH HUMAN POPULATIONS.", {}, 'T', false, 20},
    {"VAMPIRES CAN SURVIVE ON ANIMAL BLOOD INDEFINITELY.", {}, 'F', false, 21},
    {"A VAMPIRE'S REFLECTION CAN BE SEEN IN MIRRORED SURFACES.", {}, 'F', false, 22},
    {"VAMPIRES CAN CROSS FLOWING WATER IF CARRIED.", {}, 'T', false, 23},

    // City Multiple Choice Questions (8 questions) - Harder
    {"VAMPIRES HUNT MOST DURING:", {"NEW MOON", "FULL MOON", "EQUINOX"}, 'B', true, 24},
    {"VAMPIRE WEAKNESSES INCLUDE:", {"HOLY SYMBOLS", "RUNNING WATER", "BOTH"}, 'C', true, 25},
    {"TO FIND A VAMPIRE'S LAIR, LOOK FOR:", {"COLD SPOTS", "NO MIRRORS", "BOTH"}, 'C', true, 26},
    {"URBAN VAMPIRES HIDE IN:", {"SEWERS", "ABANDONED BUILDINGS", "BOTH"}, 'C', true, 27},
    {"THE MOST DANGEROUS CITY VAMPIRE IS:", {"NEWLY TURNED", "CENTURIES OLD", "FAMISHED"}, 'B', true, 28},
    {"VAMPIRES CAN BE TRACKED BY:", {"SALT CIRCLES", "BLESSED ASH", "BOTH"}, 'B', true, 29},
    {"TO STOP A VAMPIRE'S REGENERATION, USE:", {"HOLY WATER", "SILVER DUST", "BOTH"}, 'C', true, 30},
    {"VAMPIRES AVOID CROSSROADS BECAUSE:", {"OF RELIGIOUS SYMBOLS", "OF NATURAL ENERGY", "BOTH"}, 'B', true, 31},

    // ================== CASTLE STAGE ================== //
    // Castle True/False Questions (8 questions) - Most Challenging
    {"ANCIENT VAMPIRES CAN WITHSTAND SUNLIGHT.", {}, 'T', false, 32},
    {"VAMPIRE LORDS CAN CONTROL STORMS.", {}, 'T', false, 33},
    {"VAMPIRES CAN POSSESS ANIMALS.", {}, 'T', false, 34},
    {"CASTLE VAMPIRES SLEEP UPSIDE DOWN.", {}, 'F', false, 35},
    {"VLADRIC CAN SHAPE-SHIFT INTO A MIST FORM.", {}, 'T', false, 36},
    {"ANCIENT VAMPIRES ARE WEAK TO GARLIC.", {}, 'F', false, 37},
    {"VLADRIC'S CASTLE HAS NO REFLECTIVE SURFACES.", {}, 'T', false, 38},
    {"VLADRIC CAN CONTROL MINDS THROUGH EYE CONTACT.", {}, 'T', false, 39},

    // Castle Multiple Choice Questions (8 questions) - Most Challenging
    {"VLADRIC'S WEAKNESS IS:", {"HIS RING", "HIS COFFIN", "HIS LINEAGE"}, 'A', true, 40},
    {"TO DEFEAT VLADRIC, YOU MUST:", {"DESTROY HIS RELICS", "BREAK HIS DEFENSES", "BOTH"}, 'C', true, 41},
    {"THE CRIMSON GRAIL CONTAINS:", {"HIS BLOOD", "HIS SOUL", "BOTH"}, 'C', true, 42},
    {"VLADRIC'S POWER COMES FROM:", {"THE GRAIL", "ANCIENT RITES", "BOTH"}, 'C', true, 43},
    {"VLADRIC'S RING GRANTS HIM:", {"INVISIBILITY", "MIND CONTROL", "BOTH"}, 'B', true, 44},
    {"THE CASTLE'S DARK ENERGY IS MAINTAINED BY:", {"SACRIFICES", "ANCIENT RUNES", "BOTH"}, 'C', true, 45},
    {"TO BREAK VLADRIC'S DEFENSES, YOU NEED:", {"HOLY WATER", "SILVER DAGGER", "BOTH"}, 'C', true, 46},
    {"VLADRIC'S FINAL FORM IS WEAKEST TO:", {"WOODEN STAKE THROUGH HEART", "DECAPITATION", "BOTH"}, 'C', true, 47}
};



// --- PLAYER CLASS --- //
class Player {
public:
    friend class SoundEngine;
    int hp;
    int stageEnergy;
    vector<string> weapons;
    int currentStage;
    int mapPieces;
    int bossDefenses;
    bool usedHolyWater;
    bool usedSilverDagger;
    bool usedWoodenStake;
    int questionsAnswered;
    int stageQuestionsRight;
    int stageQuestionsWrong;
    //Must  have the stage introdution  before the 

    Player() : hp(STARTING_HP), stageEnergy(0), currentStage(0),
        mapPieces(0), bossDefenses(3), usedHolyWater(false),
        usedSilverDagger(false), usedWoodenStake(false),
        questionsAnswered(0), stageQuestionsRight(0), stageQuestionsWrong(0) {
    }

    void resetStageEnergy() { stageEnergy = 0; }
    void resetStageStats() {
        stageQuestionsRight = 0;
        stageQuestionsWrong = 0;
    }
    void addWeapon(const string& weapon) { 
        weapons.push_back(weapon); 
    }

    string stageIntro(string intro , int stage){
        if(stage == 0){
            intro="Welcome to stage 1:Academy";
        }else if(stage==1){
            intro="Welcome to stage 2: City";
        }else{
            intro ="Welcome to stage 3:Castle";
        }

        return " "; 
    }
};
//Tour guard must appear on screen 5 , must have a bubble that have contain information
struct TourGuard{
    int currentStage;//Keeps track of the current stage
    vector<string> clues ;   //Clue depending on the question
    string lecture ;  //  Lectures about the ancient vampires 
    void setClue(Text clue){
        clue.setString(clues[0]);
        clue.setCharacterSize(10);
        clue.setPosition({700.f,500.f});
        clue.setFillColor(Color::White);
    }
};
class Leaderboard{
    public:
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
//Method for the game page review about the game
Text pageReview(string title,int i ){ 
    Text topic(write1,title);
    if(i==1){
        topic.setFont(write1);
        topic.setCharacterSize(50.f);
        topic.setPosition({30.f,30.f});
        topic.setFillColor(Color::Red);
        topic.setOutlineThickness(5.f);
        topic.setOutlineColor(Color::Black);
    }else{
        topic.setFont(write);
        topic.setPosition({50.f,150.f});
    }
    return topic;
}
Sprite images(string nm){  //Method for creating images 
    Texture texture;
    if (!texture.loadFromFile(nm)) {
        cerr << "Error loading cover texture!" << endl;
    }
    texture.setSmooth(true);
    Sprite image(texture);
    return image;
}

int main()
{
    // --- WINDOW --- //

    RenderWindow window(VideoMode({1360, 770}), "Vampire Hunter's Chronicle"); 
    int currentScreen = 0; // 0=cover, 1=login, 2=rules1, 3=rules2, 4=rules3, 5=game, 6=gameover, 7=stagecomplete
    string playerInput;
    int totalScore = 0;

    // --- COVER PAGE --- //
    Texture coverTexture;
    if (!coverTexture.loadFromFile("Images/cover.png")) {
        cerr << "Error loading cover texture!" << endl;
        return -1;
    }
    coverTexture.setSmooth(true);
    Sprite coverSprite(coverTexture);

    Text coverText1(bloodyFont, "Welcome to Vampire Hunter's Chronicle\n        Hunt or be hunted ", 70);
    Text coverText2(font3, " START", 80);

    //Start button  for the game 
    CircleShape startCircle(50.f);
    startCircle.setFillColor(Color(128,0,0));
    startCircle.setPosition({600.f,400.f});
    startCircle.setScale({2.f,1.f});

    //Game description button
    Text description(font3,"Game Overview",50);
    description.setPosition({180.f,520.f});
    description.setFillColor(Color::Black);

    CircleShape circleButton(50.f);
    circleButton.setPosition({150.f,500.f});
    circleButton.setScale({2.f,1.f});

    //Rules Button
    Text rulesT(font3,"Game Rules",50);
    rulesT.setPosition({1000.f,520.f});
    rulesT.setFillColor(Color::Black);

    CircleShape rulesB(50.f);
    rulesB.setPosition({970.f,500.f});
    rulesB.setScale({2.f,1.f});


    //Sounds
    SoundBuffer buffer("Sounds/vampire.mp3");  //Background Sound for Game review and
    Sound background(buffer);
    background.setVolume(50.f);
    background.setPitch(0.75f);
    //background.play();

    SoundBuffer buffer2("Sounds/vampire.mp3");
    Sound chp1Sound(buffer2);

    SoundBuffer buffer3("Sounds/chapter2.mp3");
    Sound chp2Sound(buffer3);

    SoundBuffer buffer4("Sounds/vampire.mp3");
    Sound chp3Sound(buffer4);

    SoundBuffer buffer6("Sounds/chapter1.mp3");
    Sound stageEntrySound(buffer6);

    SoundBuffer buffer5("Sounds/timeUp.mp3");
    Sound timeUp(buffer5);

    //-----Overview Page----//
    Text overviewTitle= pageReview("The Vampire Hunter's Chronicle Game QUIz",1);
    Text info = pageReview(IntroStoryLine,0);
    Text chp1Title= pageReview("Chapter One:The Academy",1);
    Text chp1Story = pageReview(chp1StoryLine,0);
    Text chp2Title= pageReview("Chapter Two: The City",1);
    Text chp2Story = pageReview(chp2StoryLine,0);
    Text chp3Title= pageReview("Chapter Three: The Castle",1);
    Text chp3Story= pageReview(chp3StoryLine,0);

    //Next Button
    Text  nextB(write1,"NEXT",30.f);
    nextB.setPosition({1200.f,700.f});
    nextB.setFillColor(Color::Red);

    //Back button
    Text back(bloodyFont,"BACK",30.f);
    back.setFillColor(Color::Red);
    back.setPosition({50.f,710.f});



    //Button at Leaderboard
    Text restartButton(bloodyFont,"Restart a game",50);
    restartButton.setFillColor(Color::Red);
    restartButton.setPosition({50.f,510.f});

    Text quit(bloodyFont,"Quit",50);
    quit.setFillColor(Color::Red);
    quit.setPosition({1000.f,510.f});


    // --- LOGIN PAGE ----//
    Texture loginTexture;
    if (!loginTexture.loadFromFile("Images/cover.png")) {
        cerr << "Error loading login texture!" << endl;
        return -1;
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

    // --- RULES PAGE 1 --- //
    Texture rulesTexture;
    if (!rulesTexture.loadFromFile("Images/Rules.png")) {
        cerr << "Error loading rules texture!" << endl;
        return -1;
    }
    rulesTexture.setSmooth(true);
    Sprite rulesSprite(rulesTexture);

    Text rules1Text1(write1, "Game Rules", 50);
    rules1Text1.setFillColor(Color::Red);
    rules1Text1.setOutlineThickness(5.f);
    rules1Text1.setOutlineColor(Color::Black);
    Text rules1Text2(write, "Gothic horror trivia - RPG where you battle vampires through knowledge,\n"
        "Last graduate of a fallen hunter academy must answer questions correctly,\n"
        "Unlock sacred weapons and progress through three deadly stages", 30);
    Text rules1Text3(write, "Health & Energy System\n"
        "* Starting HP: 10\n"
        "* Starting time: 30 sec per question\n"
        "* Correct answer: +1 Energy (per stage)\n"
        "* Wrong answer: -2 HP (varies by stage)\n"
        "* Time penalty on wrong answer (varies by stage)\n"
        "* Game over at 0 HP", 30);

    // --- RULES PAGE 2 --- //
    Text rules2Text2(write, "Stage Mechanics\n"
        "* ACADEMY: -2 HP per wrong | +1 Energy per correct\n"
        "* CITY: -2 HP | +1 Energy per correct\n"
        "* CASTLE: -4 HP| +1 Energy + +1 Energy per correct", 30);
    Text rules2Text3(write, "Important Notes\n"
        "* Energy and weapons resets when advancing stages\n"
        "* Weapons unlock immediately at 3 Energy\n"
        "* Multiple weapons can be earned per stage (3 Energy = 1 weapon)", 30);
    Text rules2Text4(write, "Victory Conditions\n"
        "* Unleash all three weapons in cinematic finisher\n"
        "* Shatter Vladric's reign... but inherit his curse\n"
        "* Unlock 'Daywalker Mode' for New Game+", 30);

    // --- RULES PAGE 3 --- //
    Text rules3Text5(write, "Weapon Effects\n"
        "| Stage    | Weapon       | Effect                         \n"
        "|----------|--------------|--------------------------------\n"
        "| Academy  | Silver Dagger| Next wrong answer costs 0 HP   \n"
        "| City     | Holy Water   | No time penalty for next wrong answer \n"
        "| Castle   | Wooden Stake | Auto-corrects 1 wrong answer    ", 30);
    Text rules3Text6(write, "Game Over Consequences\n"
        "* ACADEMY: Become chained thrall\n"
        "* CITY: Corpse becomes warning (hangs in background)\n"
        "* CASTLE: Rise as Vladric's lieutenant (unlocks Vampire Mode)", 30);

    // --- GAME SCREEN --- //
    Texture gameTexture;
    if (!gameTexture.loadFromFile("Images/2.png")) {
        cerr << "Error loading game texture!" << endl;
        return -1;
    }
    gameTexture.setSmooth(true);
    Sprite gameSprite(gameTexture);

    Text questionText(bloodyFont, "", 30);
    Text optionTexts[3] = { Text(bloodyFont, "", 20), Text(bloodyFont, "", 20), Text(bloodyFont, "", 20) };
    Text statusText(bloodyFont, "", 30);
    Text weaponText(bloodyFont, "", 30);
    Text resultText(bloodyFont, "", 50);
    Text stageText(bloodyFont, "", 45);
    RectangleShape answerButtons[3];

    Text gameContinueButtonText(bloodyFont, "CONTINUE", 60);
    gameContinueButtonText.setPosition({ 500.f, 500.f });
    gameContinueButtonText.setFillColor(Color::White);

    //Timer display
    Text timerLabel(bloodyFont, "Time:", 60);
	timerLabel.setPosition({ 550.f, 30.f });
	timerLabel.setFillColor(Color::Red);

	Text timerText(bloodyFont, "10", 60);
	timerText.setPosition({ 700.f, 30.f });
	timerText.setStyle(Text::Bold);
	timerText.setFillColor(Color::Red);

    // --- STAGE COMPLETE SCREEN --- //
    Text stageCompleteText(bloodyFont, "", 60);
    Text statsText1(bloodyFont, "", 40);
    Text statsText2(bloodyFont, "", 40);
    Text stageContinueText(bloodyFont, "CONTINUE", 60);
    stageContinueText.setPosition({ 500.f, 500.f });
    stageContinueText.setFillColor(Color::Green);

    // --- GAME OVER SCREEN --- //
    Text gameOverText(bloodyFont, "", 40);
    Text gameOverContinueText(bloodyFont, "CLICK ANYWHERE TO EXIT", 40);
    //Must have the leadboard have a reference of the leadernoard

    //ChapterIntro
    Texture chp1("Images/2.png");
    Sprite chp1Image(chp1);
    Text Academy(bloodyFont,"Academy Stage",50);
    Academy.setPosition({300.f,50.f});
    Academy.setFillColor(Color::Red);
    Text intro1(write,"Welcome Initiate...\n\nYou stand within the candlelit halls of the Crimson Academy-where knowledge is your \nfirst weapon and ignorance is fatal. The ancient professors watch from \nthe shadows as you begin your Trials.\nLearn the lore, master the myths, and earn your fangs.\n\nYour first test awaits. Succeed... or be forgotten.");
    intro1.setPosition({70.f,300.f});

    //Each chapter must have multiple images in the background.
    //Chapter One images
    vector<Sprite>c1Images={images("image3.png"),images("image3.png")};

    vector<Sprite>Image={images("image3.png"),images("City.png"),images("Castle.png")};

    Sprite chp2Image=images("Images/City.png");
    Text City(bloodyFont,"City Stage",50);
    City.setPosition({300.f,50.f});
    City.setFillColor(Color::Red);
    Text intro2(write,"The hunt begins...\n\nDarkness grips the city. Neon lights flicker as ancient blood stalks modern streets. \nUrban vampires wear human masks, and every alley may be a trap. \nYou must use your training to uncover the hidden, the cursed, and the damned.\nAdapt or be prey. The night is watching.");
    intro2.setPosition({70.f,300.f});
    

    Texture chp3("Images/Castle.png");
    Sprite chp3Image(chp3);
    Text Castle(bloodyFont,"Castle Stage",50);
    Castle.setPosition({300.f,50.f});
    Castle.setFillColor(Color::Red);
    Text intro3(write,"This is the final threshold...\n\nThe air grows colder as you cross into Castle Noctis—Vladric's fortress of dread. \nMagic thickens the mist, and shadows whisper your name. Within these walls, \ntrivia becomes survival, and only mastery can break the curse.\nThe Lord of Blood stirs... Will you face him, or fall to the dark?");
    intro3.setPosition({70.f,300.f});
    
    vector<Sprite> introImages={chp1Image,chp2Image,chp3Image};
    vector<Text> introTexts={intro1,intro2,intro3};
    vector<Text>  introTitles={Academy,City,Castle};

    Text start(bloodyFont,"Let Begin",30.f);
    start.setPosition({1100.f,700.f});
    start.setFillColor(Color::Red);
    // --- SET POSITIONS --- //
    coverText1.setPosition({ 50.f, 30.f });
    coverText2.setPosition({ 620.f, 400.f });
    username.setPosition({ 150.f, 190.f });
    inputText.setPosition({ 250.f, 190.f });
    textField.setPosition({ 250.f, 190.f });
    rules1Text1.setPosition({ 500.f, 100.f });
    rules1Text2.setPosition({ 140.f, 190.f });
    rules1Text3.setPosition({ 140.f, 380.f });
    rules2Text2.setPosition({ 140.f, 190.f });
    rules2Text3.setPosition({ 140.f, 380.f });
    rules2Text4.setPosition({ 140.f,550 });
    rules3Text5.setPosition({ 140.f, 190.f });
    rules3Text6.setPosition({ 140.f, 480.f });
    questionText.setPosition({ 400.f, 200.f });
    statusText.setPosition({ 20.f, 20.f });
    weaponText.setPosition({ 1000.f, 60.f });
    stageText.setPosition({ 20.f, 100.f });
    resultText.setPosition({ 400.f, 300.f });
    gameOverText.setPosition({ 100.f, 300.f });
    gameOverContinueText.setPosition({ 300.f, 800.f });
    stageCompleteText.setPosition({ 250.f, 100.f });
    statsText1.setPosition({ 150.f, 300.f });
    statsText2.setPosition({ 150.f, 400.f });

    // --- SET COLORS --- //
    coverText1.setFillColor(Color::White);
    coverText2.setFillColor(Color::Black);
    username.setFillColor(Color::Black);
    inputText.setFillColor(Color::White);
    textField.setFillColor(Color(30, 30, 30, 200));
    textField.setOutlineThickness(2.f);
    textField.setOutlineColor(Color::Black);
    questionText.setFillColor(Color::White);
    statusText.setFillColor(Color::White);
    weaponText.setFillColor(Color::White);
    stageText.setFillColor(Color::Red);
    stageText.setStyle(Text::Bold);
    gameOverText.setFillColor(Color::Red);
    gameOverText.setStyle(Text::Bold);
    gameOverContinueText.setFillColor(Color::White);
    stageCompleteText.setFillColor(Color::Red);
    statsText1.setFillColor(Color::White);
    statsText2.setFillColor(Color::White);

    //--- STAT BARS --- //
	Text weaponsLabel(bloodyFont, "WEAPONS:", 40);
	weaponsLabel.setPosition({ 20.f, 30.f });
	weaponsLabel.setFillColor(Color::Red);

	Text weaponsText(bloodyFont, "NONE", 30);
	weaponsText.setPosition({ 190.f, 35.f });
	weaponsText.setFillColor(Color::Yellow);


	RectangleShape hpBarBack(Vector2f(300.f, 20.f));
	RectangleShape hpBar(Vector2f(300.f, 20.f));
	RectangleShape energyBarBack(Vector2f(300.f, 20.f));
	RectangleShape energyBar(Vector2f(0.f, 20.f));
	RectangleShape questionsBarBack(Vector2f(300.f, 20.f));
	RectangleShape questionsBar(Vector2f(0.f, 20.f));
	Text hpLabel(bloodyFont, "HP", 24);
	Text energyLabel(bloodyFont, "ENERGY", 24);
	Text questionsLabel(bloodyFont, "QUESTIONS", 24);

	questionsBarBack.setPosition({ 1000.f, 80.f });
	questionsBarBack.setFillColor(Color(80, 0, 0));
	questionsBar.setPosition({ 1000.f, 80.f });
	questionsBar.setFillColor(Color::Red);
	questionsLabel.setPosition({ 850.f, 80.f });
	questionsLabel.setFillColor(Color::Red);
	hpBarBack.setPosition({ 1000.f, 20.f });
	hpBarBack.setFillColor(Color(0, 50, 0));
	hpBar.setPosition({ 1000.f, 20.f });
	hpBar.setFillColor(Color::Green);
	energyBarBack.setPosition({ 1000.f, 50.f });
	energyBarBack.setFillColor(Color(0, 0, 80));
	energyBar.setPosition({ 1000.f, 50.f });
	energyBar.setFillColor(Color::Blue);
	hpLabel.setPosition({ 850.f, 20.f });
	hpLabel.setFillColor(Color::Green);
	energyLabel.setPosition({ 850.f, 50.f });
	energyLabel.setFillColor(Color::Blue);

    // --- GAME STATE --- //
    Player player;
    vector<Question> currentQuestions;
    bool gameOver = false;
    bool inCityPenalty = false;
    float penaltyTime = 0.f;
    Clock cityPenaltyClock;
    bool showResult = false;
    bool resultCorrect = false;
    bool stageTransition = false;
    float transitionTime = 30.f;
    Clock transitionClock;
    Question currentQuestion;
    Clock questionClock;
    float timeRemaining = QUESTION_TIME_LIMIT;
    bool timeExpired = false;

    // --- GAME FUNCTIONS --- //
    auto updateWeaponsDisplay = [&]() {
        string weaponsStr = "NONE";
        if (!player.weapons.empty()) {
            weaponsStr = "";
            vector<string> currentStageWeapons; // Filter weapons by stage
            for (const auto& weapon : player.weapons) {
                if ((player.currentStage == 0 && weapon == "SILVER DAGGER") ||
                    (player.currentStage == 1 && weapon == "HOLY WATER") ||
                    (player.currentStage == 2 && weapon == "WOODEN STAKE")) {
                    currentStageWeapons.push_back(weapon); // Only add stage-relevant weapons
                }
            }
    
            if (!currentStageWeapons.empty()) {
                int silverDaggers = count(currentStageWeapons.begin(), currentStageWeapons.end(), "SILVER DAGGER");
                int holyWaters = count(currentStageWeapons.begin(), currentStageWeapons.end(), "HOLY WATER");
                int woodenStakes = count(currentStageWeapons.begin(), currentStageWeapons.end(), "WOODEN STAKE");
    
                if (silverDaggers > 0) weaponsStr += to_string(silverDaggers) + " SILVER DAGGER" + (silverDaggers > 1 ? "S " : " ");
                if (holyWaters > 0) weaponsStr += to_string(holyWaters) + " HOLY WATER" + (holyWaters > 1 ? "S " : " ");
                if (woodenStakes > 0) weaponsStr += to_string(woodenStakes) + " WOODEN STAKE" + (woodenStakes > 1 ? "S " : " ");
    
                if (!weaponsStr.empty()) weaponsStr.pop_back(); // Remove trailing space
            }
            else {
                weaponsStr = "NONE"; // No weapons for this stage
            }
        }
        weaponsText.setString(weaponsStr);
    };
    auto loadStageQuestions = [&]() {
        player.resetStageStats();
        currentQuestions.clear();
        updateWeaponsDisplay();
        int questionsPerStage = 16; 
        int startIdx = player.currentStage * questionsPerStage;

        vector<Question> tfQuestions;
        vector<Question> mcQuestions;

        for (int i = 0; i < questionsPerStage; i++) {
            Question q = questionBank[startIdx + i];
            if (q.isMultipleChoice) {
                mcQuestions.push_back(q);
            }
            else {
                tfQuestions.push_back(q);
            }
        }

        auto rng = default_random_engine(random_device{}());
        shuffle(tfQuestions.begin(), tfQuestions.end(), rng);
        shuffle(mcQuestions.begin(), mcQuestions.end(), rng);

        for (int i = 0; i < 5; i++) {  //To have 10 questions on each stage
            currentQuestions.push_back(tfQuestions[i]);
            currentQuestions.push_back(mcQuestions[i]);
        }

        shuffle(currentQuestions.begin(), currentQuestions.end(), rng);
    };

    auto setupQuestion = [&]() {
        timeRemaining = QUESTION_TIME_LIMIT;
        questionClock.restart();
        timeExpired = false;

        if (currentQuestions.empty()) {
            if (player.questionsAnswered >= QUESTIONS_PER_STAGE) {
                if (player.currentStage < 2) {
                    currentScreen = 7; // Show stage completion screen
                    stageCompleteText.setString(STAGES[player.currentStage] + " STAGE COMPLETED!");

                    string stats1 = "QUESTIONS: " + to_string(QUESTIONS_PER_STAGE) +
                        " | RIGHT: " + to_string(player.stageQuestionsRight) +
                        " | WRONG: " + to_string(player.stageQuestionsWrong);

                    string stats2 = "WEAPONS COLLECTED: ";
                    for (const auto& w : player.weapons) {
                        if ((player.currentStage == 0 && w == "SILVER DAGGER") ||
                            (player.currentStage == 1 && w == "HOLY WATER") ||
                            (player.currentStage == 2 && w == "WOODEN STAKE")) {
                            stats2 += w + " ";
                        }
                    }

                    statsText1.setString(stats1);
                    statsText2.setString(stats2);
                    return;
                }
                loadStageQuestions();
                player.questionsAnswered = 0;
            }
        }

        currentQuestion = currentQuestions.back();
        player.questionsAnswered++;

        questionText.setString(currentQuestion.text);

        if (currentQuestion.isMultipleChoice) {
            for (int i = 0; i < 3; i++) {
                optionTexts[i].setString(currentQuestion.options[i]);
                optionTexts[i].setPosition({ 400.f, 300.f + i * 100.f });
                answerButtons[i].setPosition({ 300.f, 300.f + i * 80.f });
                answerButtons[i].setSize(Vector2f(700.f, 80.f));
                answerButtons[i].setFillColor(Color(30, 30, 30, 200));
                answerButtons[i].setOutlineThickness(2.f);
                answerButtons[i].setOutlineColor(Color::Black);
            }
        }
        else {
            optionTexts[0].setString("TRUE (T)");
            optionTexts[1].setString("FALSE (F)");
            optionTexts[2].setString("");

            for (int i = 0; i < 2; i++) {
                optionTexts[i].setPosition({ 500.f, 300.f + i * 100.f });
                answerButtons[i].setPosition({ 300.f, 300.f + i * 80.f });
                answerButtons[i].setSize(Vector2f(700.f, 80.f));
                answerButtons[i].setFillColor(Color(30, 30, 30, 200));
                answerButtons[i].setOutlineThickness(2.f);
                answerButtons[i].setOutlineColor(Color::Black);
            }

            answerButtons[2].setSize(Vector2f(0.f, 0.f));
        }
        };

    auto handleCorrectAnswer = [&]() {
        player.stageEnergy++;
        player.stageQuestionsRight++;

        if (player.stageEnergy >= 3) {
            string weapon = STAGE_WEAPONS.at(STAGES[player.currentStage]);
            player.addWeapon(weapon);
            updateWeaponsDisplay();
            player.stageEnergy -= 3;
            resultText.setString(resultText.getString() + "\nUNLOCKED " + weapon + "!");
        }

        if (player.currentStage == 1) {  //Stage 2
            player.mapPieces++;
            if (player.mapPieces >= 3) {  //If your HP if greater than  3 then you may procced to another stage
                player.currentStage++;
                player.resetStageEnergy();
                player.questionsAnswered = 0;
                loadStageQuestions();
                stageTransition = true;
                transitionTime = 60.0f;   //Making the transition time be 1 minutes
                transitionClock.restart();
            }else{
                player.resetStageEnergy();
                player.questionsAnswered=0;
                loadStageQuestions();
                stageTransition=false;
            }
        }
        else if (player.currentStage == 2) {  //Stage 3 
            player.bossDefenses--;
            if (player.bossDefenses <= 0) {
                gameOver = true;
                currentScreen = 6;
                gameOverText.setString("FINAL SHOWDOWN!\n\nYOU UNLEASH ALL WEAPONS!\nVLADRIC CRUMBLES TO DUST...\nBUT HIS CURSE LINGERS IN YOUR VEINS.");
            }
        }
        };

    auto handleWrongAnswer = [&]() {
        player.stageQuestionsWrong++;

        // Check for Silver Dagger effect (Academy weapon)
        if (!player.usedSilverDagger &&
            find(player.weapons.begin(), player.weapons.end(), "SILVER DAGGER") != player.weapons.end() &&
            player.currentStage == 0) {
            player.usedSilverDagger = true;
            updateWeaponsDisplay();
            resultText.setString("SILVER DAGGER SAVES YOU! -0 HP\nNO TIME PENALTY");
            resultText.setFillColor(Color::Green);
            return;
        }

        // Check for Holy Water effect (City weapon)
        if (!player.usedHolyWater &&
            find(player.weapons.begin(), player.weapons.end(), "HOLY WATER") != player.weapons.end() &&
            player.currentStage == 1) {
            player.usedHolyWater = true;
            handleCorrectAnswer();
            resultText.setString("HOLY WATER SAVES YOU! ANSWER CORRECTED\nNO TIME PENALTY");
            resultText.setFillColor(Color::Green);
            return;
        }

        // Check for Wooden Stake effect (Castle weapon)
        if (!player.usedWoodenStake &&
            find(player.weapons.begin(), player.weapons.end(), "WOODEN STAKE") != player.weapons.end() &&
            player.currentStage == 2) {
            player.usedWoodenStake = true;
            resultText.setString("WOODEN STAKE DEFEATS MINOR ENEMY!\nNO TIME PENALTY");
            resultText.setFillColor(Color::Green);
            return;
        }

        int damage = (player.currentStage == 0) ? 2 : (player.currentStage == 1) ? 2 : 4;
        player.hp -= damage;

        string penaltyText = "WRONG! ";
        if (player.currentStage == 0) {
            penaltyText += "-2 HP";
        }
        else if (player.currentStage == 1) {
            penaltyText += "-2 HP, -5s ON NEXT QUESTION";
            inCityPenalty = true;
            penaltyTime = 5.0f;
            cityPenaltyClock.restart();
        }
        else if (player.currentStage == 2) {
            penaltyText += "-4 HP, -10s ON NEXT QUESTION";
            inCityPenalty = true;
            penaltyTime = 10.0f;
            cityPenaltyClock.restart();
        }

        resultText.setString(penaltyText);
        resultText.setFillColor(Color::Red);

        if (player.hp <= 0) {
            gameOver = true;
            currentScreen = 6;
            gameOverText.setString("YOU DIED\n\n");
            switch (player.currentStage) {
            case 0: gameOverText.setString(gameOverText.getString() + "YOU AWAKEN AS VLADRIC'S THRALL..."); break;
            case 1: gameOverText.setString(gameOverText.getString() + "YOUR CORPSE HANGS FROM PRAGUE'S CLOCK TOWER..."); break;
            case 2: gameOverText.setString(gameOverText.getString() + "YOU RISE AS VLADRIC'S NEW LIEUTENANT!"); break;
            }
        }
    };
    auto updateStatusText = [&]() {
        // Update HP and energy bars
        hpBar.setSize(Vector2f(300.f * (player.hp / float(STARTING_HP)), 20.f));
        energyBar.setSize(Vector2f(300.f * (player.stageEnergy / 3.f), 20.f));
    
        // Add this new line to update questions progress bar
        questionsBar.setSize(Vector2f(300.f * (player.questionsAnswered / float(QUESTIONS_PER_STAGE)), 20.f));
    
        // Update timer display
        timerText.setString(to_string(static_cast<int>(timeRemaining)));
    };

    // Initial question load
    loadStageQuestions();

    // Add initial transition for Academy stage
    stageTransition = true;
    transitionTime = 10.0f;
    transitionClock.restart();
    Clock timer;
    Texture texture("Images/cover.png");
    texture.setSmooth(true);
    Sprite sprite(texture);
    multimap<int, string, greater<>> userScores;
    Texture texture1("Images/Medal1.jpg");

    Sprite sprt(texture1);
    Sprite sprt2(texture1);
    sprt.setPosition({ 500.f, 110.f });
    sprt2.setPosition({ 850.f, 110.f }); 

    Clock o;
    Leaderboard board;
    bool isGameOver=false;
    int count =0;
    while (window.isOpen())
    {
        while (const optional event = window.pollEvent())
        {
            if (event->is<Event::Closed>()) {
                window.close();
            }
            // Screen navigation
            if (auto* mouse = event->getIf<Event::MouseButtonReleased>())
            {
                Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));

                if(currentScreen == 0){     //Cover page 
                   if(startCircle.getGlobalBounds().contains(mousePos)){ //Display login and start game 
                        currentScreen = 1;  //Log in page 
                        setupQuestion();
                    }
                    if(circleButton.getGlobalBounds().contains(mousePos)){   //Game description
                        currentScreen=2;   //Page for the Game Overview
                    }
                    if(rulesB.getGlobalBounds().contains(mousePos)){  //Rules
                        currentScreen=9;  
                    }
                }    
                else if (currentScreen == 1)  //Login page
                {
                    if (backButton.getGlobalBounds().contains(mousePos))
                        currentScreen=0;
                    else if (submitButton.getGlobalBounds().contains(mousePos))
                        currentScreen = 12; //Start Game
                        //stageEntrySound.play();
                }
                //Rule screen
                else if (currentScreen == 2){
                    if(nextB.getGlobalBounds().contains(mousePos)){
                        currentScreen=3;
                    }
                    if(back.getGlobalBounds().contains(mousePos)){
                        currentScreen=0;
                    }    
                }
                else if (currentScreen == 3 ){
                    if(nextB.getGlobalBounds().contains(mousePos)){
                        currentScreen=4;
                    }
                    if(back.getGlobalBounds().contains(mousePos)){
                        currentScreen=2;
                    } 
                }
                else if (currentScreen == 4)
                {
                    if(nextB.getGlobalBounds().contains(mousePos)){
                        currentScreen=8;
                        setupQuestion();
                    }
                    if(back.getGlobalBounds().contains(mousePos)){
                        currentScreen=3;
                    } 

                }else if (currentScreen == 8)
                {
                    if(nextB.getGlobalBounds().contains(mousePos)){
                        currentScreen = 0;   //Returns to cover page
                    }
                    if(back.getGlobalBounds().contains(mousePos)){
                        currentScreen=4;
                    }
                }else if(currentScreen == 9){
                    if(nextB.getGlobalBounds().contains(mousePos)){
                        currentScreen = 10;   //Returns to cover page
                    }
                    if(back.getGlobalBounds().contains(mousePos)){
                        currentScreen=0;
                    }
                }else if(currentScreen == 10){
                    if(nextB.getGlobalBounds().contains(mousePos)){
                        currentScreen = 11;   //Returns to cover page
                    }
                    if(back.getGlobalBounds().contains(mousePos)){
                        currentScreen=9;
                    }
                }
                else if(currentScreen == 11){
                    if(nextB.getGlobalBounds().contains(mousePos)){
                        currentScreen = 0;   //Returns to cover page
                    }
                    if(back.getGlobalBounds().contains(mousePos)){
                        currentScreen=10;
                    }
                }else if(currentScreen == 12 && start.getGlobalBounds().contains(mousePos)){
                    setupQuestion();
                    currentScreen=5;
                    //stageEntrySound.stop();
                }
                
                //Question Section.
                else if (currentScreen == 5 && !showResult && !stageTransition && !inCityPenalty)
                {
                    //This handle the answers wrong or right and shwo if the asnwer is correct or not 
                    for (int i = 0; i < 3; i++) {
                        if (answerButtons[i].getGlobalBounds().contains(mousePos)) {
                            char answer;

                            if (!currentQuestion.isMultipleChoice) {
                                answer = (i == 0) ? 'T' : 'F';
                            }
                            else {
                                answer = 'A' + i;
                            }

                            bool correct = (toupper(answer) == toupper(currentQuestion.correctAnswer));
                            currentQuestions.pop_back();

                            if (correct) {
                                handleCorrectAnswer();
                                resultText.setString("CORRECT! +1 ENERGY");
                                resultText.setFillColor(Color::Green);
                            }
                            else {
                                handleWrongAnswer();
                                if (!gameOver) {
                                    resultText.setString(resultText.getString());
                                    resultText.setFillColor(Color::Red);
                                }
                            }
                            showResult = true; //Showing the result for each question ,must remove this screen , only update the hp 
                            updateStatusText(); //text
                            break;
                        }
                    }
                }
                //Screen five shows result and continue button
                else if (currentScreen == 5 && showResult && gameContinueButtonText.getGlobalBounds().contains(mousePos))
                {
                    showResult = false;
                    if (!gameOver) setupQuestion();//Setup each new question
                }
                else if (currentScreen == 7 && stageContinueText.getGlobalBounds().contains(mousePos))
                {
                    player.currentStage++;
                    player.resetStageEnergy();
                    player.questionsAnswered = 0;
                    loadStageQuestions();
                    stageTransition = true;
                    transitionTime = 3.0f;
                    transitionClock.restart();
                    currentScreen = 5;
                }
                else if (currentScreen == 6) // Game over screen - click quit to exit or start a new game
                {
                    if(quit.getGlobalBounds().contains(mousePos)){
                        window.close();
                    }else if (restartButton.getGlobalBounds().contains(mousePos)){
                        currentScreen=5;
                    }

                }
            }

            // Text input (login screen only)
            if (currentScreen == 1)
            {
                if (auto* text = event->getIf<Event::TextEntered>())
                {
                    inputText.setString("");  //Set the string to be empty
                    if (text->unicode == 8 && !playerInput.empty()) {
                        playerInput.pop_back();
                    }
                    else if (text->unicode < 128 && text->unicode != 13 && playerInput.length() < 20) {
                        playerInput += static_cast<char>(text->unicode);
                    }
                    inputText.setString(playerInput);
                }
            }
        }

        // Update game state
        if (currentScreen == 5) {
            if (!showResult && !stageTransition && !inCityPenalty) {
                timeRemaining = QUESTION_TIME_LIMIT - questionClock.getElapsedTime().asSeconds();
                if (timeRemaining <= 0 && !timeExpired) {
                    timeExpired = true;
                    currentQuestions.pop_back();
                    handleWrongAnswer();
                    resultText.setString("TIME'S UP! THE VAMPIRE STRIKES BACK");
                    resultText.setFillColor(Color::Red);
                    showResult = true;
                    updateStatusText();
                }
            }

            if (inCityPenalty) {
                penaltyTime -= cityPenaltyClock.restart().asSeconds();
                if (penaltyTime <= 0) {
                    inCityPenalty = false;
                    if (player.hp > 0) {
                        // Apply time penalty to next question
                        timeRemaining = max(0.0f, QUESTION_TIME_LIMIT - ((player.currentStage == 1) ? 5.0f : 10.0f));
                        questionClock.restart();
                    }
                    else {
                        currentScreen = 6;
                    }
                }
            }

            if (stageTransition) {
                transitionTime -= transitionClock.restart().asSeconds();
                if (transitionTime <= 0) {
                    stageTransition = false;
                    setupQuestion();
                }
            }
            //Update status display
            updateStatusText();
        }

        //Button hover effects
        Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
        
        float count =0.f;
        while(count<=4.f){
            if(static_cast<int>(timer.getElapsedTime().asSeconds())%2!=0){
                coverText1.setFillColor(Color(128,128,128));
            }else{
                coverText1.setFillColor(Color(128,0,0));
            }
            count++;
        }

        if (currentScreen == 0)   //Cover Screen 
        {
            if (startCircle.getGlobalBounds().contains(mousePos))
                startCircle.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Blue: Color::Blue);
            else
                startCircle.setFillColor(Color(128,0,0));
            if (circleButton.getGlobalBounds().contains(mousePos))
                circleButton.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Blue: Color::Blue); 
            else 
                circleButton.setFillColor(Color(128,0,0));
            if (rulesB.getGlobalBounds().contains(mousePos))
                rulesB.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Blue: Color::Blue);
            else
                rulesB.setFillColor(Color(128,0,0));        
        }
        else if (currentScreen == 1)   //LogIn Page
        {
            if (backButton.getGlobalBounds().contains(mousePos))
                backButton.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Green : Color::Green);
            else
                backButton.setFillColor(Color::Black);

            if (submitButton.getGlobalBounds().contains(mousePos))
                submitButton.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Green : Color::Green);
            else
                submitButton.setFillColor(Color::Black);
        }
        else if (currentScreen == 2  || currentScreen==10 || currentScreen==3 || currentScreen==9 || currentScreen==4 || currentScreen==11 || currentScreen==8|| currentScreen==11)
        {
            if (nextB.getGlobalBounds().contains(mousePos)){
                nextB.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Red : Color::Red);
            }else{
                nextB.setFillColor(Color::Green);
            }
            if (back.getGlobalBounds().contains(mousePos)){
                back.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Red : Color::Red);
            }else{
                back.setFillColor(Color::Green);
            }    
        }
        else if (currentScreen==12){
            if (start.getGlobalBounds().contains(mousePos))
                start.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Green : Color::Green);
            else
                start.setFillColor(Color::Red);
        }
        else if (currentScreen == 5 && showResult)
        {    //Change the color of the continue button
            if (gameContinueButtonText.getGlobalBounds().contains(mousePos)){
                gameContinueButtonText.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Green : Color::Green);
            }else{
                gameContinueButtonText.setFillColor(Color::White);
            }    
        }
        else if (currentScreen == 7)
        {
            if (stageContinueText.getGlobalBounds().contains(mousePos)){
                stageContinueText.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Red : Color::Red);
            }else{
                stageCompleteText.setFillColor(Color::White);
            }    
        }else if(currentScreen==6){
            if (restartButton.getGlobalBounds().contains(mousePos)){
                restartButton.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Red : Color::Red);
            }else{
                restartButton.setFillColor(Color::White);
            } 

            if (quit.getGlobalBounds().contains(mousePos)){
                quit.setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ? Color::Red : Color::Red);
            }else{
                quit.setFillColor(Color::White);
            } 
        }

        // Drawing
        window.clear();

        switch (currentScreen)
        {
        case 0: // Cover
            window.draw(coverSprite);
            window.draw(startCircle);
            window.draw(coverText1);
            window.draw(coverText2);
            window.draw(circleButton);
            window.draw(description);
            window.draw(rulesB);
            window.draw(rulesT);
            break;
        case 1: // Login
            window.draw(loginSprite);
            window.draw(page);
            window.draw(title);
            window.draw(username);
            window.draw(textField);
            window.draw(inputText);
            window.draw(backButton);
            window.draw(submitButton);
            break;
        
        case 2:   //Game overview Story Line
            window.draw(rulesSprite);  //Image
            window.draw(nextB);
            window.draw(overviewTitle);
            window.draw(info);
            window.draw(back);
            break;
        
        case 3:// Game review of Chapter one
            window.draw(rulesSprite);
            window.draw(chp1Title);
            window.draw(chp1Story);
            window.draw(nextB);
            window.draw(back);
            break;
        
        case 4: // Game review of Chapter Two
            window.draw(rulesSprite);
            window.draw(chp2Title);
            window.draw(chp2Story);
            window.draw(nextB);
            window.draw(back);
            break;

        case 5: // Game
        
            //window.draw(threeButton);
            window.draw(introImages[player.currentStage]);
            window.draw(statusText);
            window.draw(weaponText);
            stageText.setString("The "+STAGES[player.currentStage]);
            if (player.hp <= 2) {
                static Clock pulseClock;
                float pulse = sin(pulseClock.getElapsedTime().asSeconds() * 6) * 50 + 205;
                hpBar.setFillColor(Color(0, pulse, 0));
            }
            else {
                hpBar.setFillColor(Color::Green);
            }

            if (stageTransition) {
                //Must have multiple images on the background.
                window.draw(introImages[player.currentStage]); //Draw a suitable image for the current Stage
                window.draw(introTexts[player.currentStage]);
                window.draw(introTitles[player.currentStage]);
            }
            else if (inCityPenalty) {
                Text penaltyText(bloodyFont, "VAMPIRE's ATTACK STUNNED YOU!\nWAIT " + to_string(int(penaltyTime)) + " SECONDS..", 50);
                penaltyText.setPosition({ 200.f, 400.f });
                penaltyText.setFillColor(Color::Red);
                window.draw(penaltyText);
            }
            else if (showResult) {    //Must remove this part 
                window.draw(resultText);
                window.draw(gameContinueButtonText);
            }
            else {//Drawing questions  
                window.draw(questionText);
                for (int i = 0; i < 3; i++) {
                    if (answerButtons[i].getSize().x > 0) {
                        if (answerButtons[i].getGlobalBounds().contains(mousePos)) {
                            answerButtons[i].setFillColor(Mouse::isButtonPressed(Mouse::Button::Left) ?
                                Color(100, 0, 0) : Color(150, 0, 0));
                        }
                        else {
                            answerButtons[i].setFillColor(Color(30, 30, 30, 200));
                        }
                        window.draw(answerButtons[i]);
                        window.draw(optionTexts[i]);
                        window.draw(timerText);
                        window.draw(timerLabel);
                        window.draw(weaponsLabel);
                        window.draw(weaponsText);
                        window.draw(stageText);
                        window.draw(hpBarBack);
                        window.draw(hpBar);
                        window.draw(energyBarBack);
                        window.draw(energyBar);
                        window.draw(hpLabel);
                        window.draw(energyLabel);
                        window.draw(questionsBarBack);
                        window.draw(questionsBar);
                        window.draw(questionsLabel);
                    }
                }
            }
            break;
        

        case 6: // Game over
            window.draw(gameSprite);
            window.draw(gameOverText);
            window.draw(gameOverContinueText);

            if (o.getElapsedTime().asSeconds() >= 5.f) {
                isGameOver = true;
            }
            break;
        

        case 7: // Stage complete
            window.draw(gameSprite);
            window.draw(stageCompleteText);
            window.draw(statsText1);
            window.draw(statsText2);
            window.draw(stageContinueText);
            break;
        case 8:   //Chapter3 Review
            window.draw(rulesSprite);
            window.draw(chp3Title);
            window.draw(chp3Story);
            window.draw(nextB); 
            window.draw(back);
            break;
        case 9:  //Rules 1
            window.draw(rulesSprite);
            window.draw(nextB);
            window.draw(rules1Text1);
            window.draw(rules1Text2);
            window.draw(rules1Text3);
            window.draw(back);
            break;
        case 10:  //Rules 2
            window.draw(rulesSprite);
            window.draw(rules1Text1);
            window.draw(rules2Text2);
            window.draw(rules2Text3);
            window.draw(rules2Text4);
            window.draw(nextB);
            window.draw(back);
            break;         
        
        case 11:   //Rules 3
            window.draw(rulesSprite);
            window.draw(rules1Text1);
            window.draw(rules3Text5);
            window.draw(rules3Text6);
            window.draw(nextB);
            window.draw(back);
            break;
        case 12:    //Chapter Intro for transition
            switch (player.currentStage)
            {
            case 0:
               window.draw(introImages[2]);
               window.draw(intro1);
               window.draw(Academy);
                break;
            case 1 :
                window.draw(chp2Image);
                window.draw(intro2);
                window.draw(City); 
                break;
            case 2: 
                window.draw(chp3Image);
                window.draw(intro3);
                window.draw(Castle);   
                break;
            }
            window.draw(start);
        } 
        if (isGameOver) {
    
            window.draw(sprite);
            window.draw(restartButton);
            window.draw(quit); 
        
            Text titleb = board.leaderBoardTitle(bloodyFont);
            Text scoreBoard = board.leaderboard(bloodyFont, userScores, playerInput, totalScore);
            window.draw(titleb);
            window.draw(scoreBoard);
            window.draw(sprt);   // medal image
            window.draw(sprt2);
        
            int numberHighlights = 0;
            if (userScores.size() % 2 != 0) {
                numberHighlights = (userScores.size() / 2) + 1;
            }
            else {
                numberHighlights = userScores.size() / 2;
            }
            float x = 340.f;
            float y = 205.f;
            for (int i = 0; i < numberHighlights; i++) {
                RectangleShape shape = board.highlights(x, y);
                window.draw(shape);
                y += 60.f;
            }
        
        }   
        window.display();
    }
    return 0; 
}