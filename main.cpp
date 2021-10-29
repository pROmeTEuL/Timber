#include "cloud.h"

#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

bool acceptInput = false;



/*
******************************
   VARIABILE PENTRU CRENGI
******************************
*/

const int NUM_BRANCHES = 6;
Sprite branches[NUM_BRANCHES];

enum class side {LEFT, RIGHT, NONE};
side branchPositions[NUM_BRANCHES];

void updateBranches (int seed)
{
    for (int i = NUM_BRANCHES - 1; i > 0; --i) {
        branchPositions[i] = branchPositions[i - 1];
    }
    srand((int)time(0) + seed);
    int r = (rand() % 5);
    switch (r) {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}

const int NUM_CLOUDS = 6;
Cloud clouds[NUM_CLOUDS];

/*
##############################
##############################
#########FUNCTIA MAIN#########
##############################
##############################
*/
int main()
{
    int latime = 1920;
    int inaltime = 1080;
    VideoMode vm(latime, inaltime);
    RenderWindow window(vm, "Timber", Style::Fullscreen);

    /*
******************************
           AUDIO
******************************
*/
    ///TAIERE
    SoundBuffer chopBuffer;
    chopBuffer.loadFromFile("sound/chop.wav");
    Sound chop;
    chop.setBuffer(chopBuffer);
    ///RIP
    SoundBuffer ripBuffer;
    ripBuffer.loadFromFile("sound/death.wav");
    Sound rip;
    rip.setBuffer(ripBuffer);
    ///OUT OF TIME
    SoundBuffer ootBuffer;
    ootBuffer.loadFromFile("sound/out_of_time.wav");
    Sound outOfTime;
    outOfTime.setBuffer(ootBuffer);

    /*
    ******************************
             TEXTURILE
    ******************************
    */

    ///FUNDAL
    Texture textureBackground;
    textureBackground.loadFromFile("graphics/background.png");
    ///COPAC
    Texture textureTree;
    textureTree.loadFromFile("graphics/tree.png");
    ///ALBINA
    Texture textureBee;
    textureBee.loadFromFile("graphics/bee.png");
    ///CRENGI
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");
    ///JUCATOR
    Texture texturePlayer;
    texturePlayer.loadFromFile("graphics/player.png");
    ///RIP
    Texture textureRip;
    textureRip.loadFromFile("graphics/rip.png");
    ///TOPOR
    Texture textureAxe;
    textureAxe.loadFromFile("graphics/axe.png");
    ///BUSTEAN
    Texture textureLog;
    textureLog.loadFromFile("graphics/log.png");
    ///COPAC_TAIAT
    Texture textureChopedTree;
    textureChopedTree.loadFromFile("graphics/tree2.png");

    /*
    ******************************
             CONFIGURARI
    ******************************
    */

    FloatRect rect;
    ///FUNDAL
    Sprite spriteBackground;
    spriteBackground.setTexture(textureBackground);
    //    spriteBackground.setPosition(0, 0);
    rect = spriteBackground.getLocalBounds();
    spriteBackground.setOrigin(rect.left,
                               rect.top);
    spriteBackground.setPosition(0, 0);
    ///COPAC
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    //    spriteTree.setPosition(810, 0);
    rect = spriteTree.getLocalBounds();
    spriteTree.setOrigin(rect.left +
                         rect.width / 2.0f,
                         rect.top);
    spriteTree.setPosition(latime / 2.0f, 0);
    ///ALBINA
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    bool beeActive = false;
    float beeSpeed = 0.0f;
    ///CRENGI
    for (int i = 0; i < NUM_BRANCHES; ++i) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);

        branches[i].setOrigin(220, 20);
    }
    ///JUCATOR
    Sprite spritePlayer;
    spritePlayer.setTexture(texturePlayer);
    spritePlayer.setPosition(580, 720);
    side playerSide = side::LEFT;
    ///RIP
    Sprite spriteRip;
    spriteRip.setTexture(textureRip);
    spriteRip.setPosition(600, 860);
    ///TOPOR
    Sprite spriteAxe;
    spriteAxe.setTexture(textureAxe);
    spriteAxe.setPosition(700, 830);
    //Aliniere cu copacul
    const float AXE_POSITION_LEFT = 700;
    const float AXE_POSITION_RIGHT = 1075;
    ///BUSTEAN
    Sprite spriteLog;
    spriteLog.setTexture(textureLog);
    spriteLog.setPosition(810, 720);
    bool logActive = false;
    float logSpeedX = 1000;
    float logSpeedY = -1500;
    ///COPAC_TAIAT
    Sprite spriteChopedTree;
    spriteChopedTree.setTexture(textureChopedTree);
    spriteChopedTree.setPosition(810, 0);
    ///DIVERSE
    //font
    Font font;
    font.loadFromFile("fonts/KOMIKAP_.ttf");
    //joaca
    Text play;
    play.setCharacterSize(100);
    play.setString("Press Enter to START!!!");
    play.setFillColor(Color::Cyan);
    play.setFont(font);
    rect = play.getLocalBounds();
    play.setOrigin(rect.left +
                   rect.width / 2.0f,
                   rect.top +
                   rect.height / 2.0f);
    play.setPosition(latime / 2.0f, inaltime / 2.0f);

    bool notPlayed = true;
    //pauza
    Text pause;
    pause.setCharacterSize(200);
    pause.setString("Game paused");
    pause.setFillColor(Color::Black);
    pause.setFont(font);

    rect = pause.getLocalBounds();
    pause.setOrigin(rect.left +
                    rect.width / 2.0f,
                    rect.top +
                    rect.height / 2.0f);
    pause.setPosition(latime / 2.0f, inaltime / 2.0f);

    bool paused = false;
    //ceas
    Clock clock;
    //bara de timp
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Magenta);
    timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal;
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;
    //scor
    int score = 0;
    Text scoreM;
    scoreM.setFont(font);
    scoreM.setString("Score = 0");
    scoreM.setCharacterSize(50);
    scoreM.setPosition(0,0);
    scoreM.setFillColor(Color::Blue);
    //scor maxim
    int highScore = 0;
    Text highScoreM;
    highScoreM.setFont(font);
    highScoreM.setString("HighScore = 0");
    highScoreM.setCharacterSize(50);
    highScoreM.setPosition(0,50);
    highScoreM.setFillColor(Color::Red);
    ////////////////////////////////////////
    //    updateBranches(1);
    //    updateBranches(2);
    //    updateBranches(3);
    //    updateBranches(4);
    //    updateBranches(5);
    bool choped = false;
    /*
    ******************************
             BUCLA WHILE
    ******************************
    */
    while (window.isOpen()) {
        window.clear(); ///STERGEREA ECRANULUI
        window.draw(spriteBackground);
        //        window.draw(spriteCloud0); ///NOR I
        //        window.draw(spriteCloud1); ///NOR II
        //        window.draw(spriteCloud2); ///NOR III
        for (int i = 0; i < NUM_CLOUDS; ++i) {
            window.draw(clouds[i]);
        }
        for (int i = 0; i < NUM_BRANCHES; ++i) {
            window.draw(branches[i]);
        }
        if (choped)
            window.draw(spriteChopedTree);
        else
            window.draw(spriteTree); ///COPACUL
        window.draw(spritePlayer); ///JUCATORUL
        window.draw(spriteAxe); ///TOPORUL
        window.draw(spriteLog); ///BUSTEANUL
        window.draw(spriteRip); ///RIP-UL
        window.draw(spriteBee); ///ALBINA
        window.draw(scoreM); ///SCORUL
        window.draw(highScoreM); ///SCORUL MAXIM
        window.draw(timeBar); ///BARA DE TIMP
        Time dt = clock.restart();

        Event event;

        while (window.pollEvent(event)) {
            if (event.type == Event::KeyReleased && !notPlayed)
            {
                acceptInput = true;

                spriteAxe.setPosition(2000,
                                      spriteAxe.getPosition().y);
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (notPlayed == true)
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                notPlayed = false;
                score = 0;
                timeRemaining = 6;
                for  (int i = 1; i < NUM_BRANCHES; ++i) {
                    branchPositions[i] = side::NONE;
                }
                spriteRip.setPosition(675, 2000);
                spritePlayer.setPosition(580, 720);
                spriteAxe.setPosition(AXE_POSITION_LEFT, 830);
                acceptInput = true;
                choped = false;
            }
        if (acceptInput)
        {
            if (Keyboard::isKeyPressed(Keyboard::P)) {
                paused = !paused;
                while(Keyboard::isKeyPressed(Keyboard::P));
            }
            if (!paused) {
                if (Keyboard::isKeyPressed(Keyboard::Right)) {
                    playerSide = side::RIGHT;
                    ++score;
                    timeRemaining += (2 / score) + .15;

                    spriteAxe.setPosition(AXE_POSITION_RIGHT,
                                          spriteAxe.getPosition().y);
                    spritePlayer.setPosition(1200, 720);

                    updateBranches(score);
                    spriteLog.setPosition(810, 720);
                    logSpeedX = -5000;
                    logActive = true;

                    acceptInput = false;
                    chop.play();
                    choped = true;
                }

                if(Keyboard::isKeyPressed(Keyboard::Left)) {
                    playerSide = side::LEFT;
                    ++score;
                    timeRemaining += (2 / score) + .15;

                    spriteAxe.setPosition(AXE_POSITION_LEFT,
                                          spriteAxe.getPosition().y);
                    spritePlayer.setPosition(580, 720);

                    updateBranches(score);
                    spriteLog.setPosition(810, 720);
                    logSpeedX = 5000;
                    logActive = true;

                    acceptInput = false;
                    chop.play();
                    choped = true;
                }
            }
            }
        if (!notPlayed) {
            if (!paused) {
                timeRemaining -= dt.asSeconds();
                timeBar.setSize(Vector2f(timeBarWidthPerSecond *
                                         timeRemaining, timeBarHeight));
                if (timeRemaining <= 0.0f) {
                    notPlayed = true;

                    play.setString("Out of time!!");

                    rect = play.getLocalBounds();
                    play.setOrigin(rect.left +
                                   rect.width / 2.0f,
                                   rect.top +
                                   rect.height / 2.0f);
                    play.setPosition(latime / 2.0f, inaltime / 2.0f);
                    outOfTime.play();
                }
                if (!beeActive) {
                    srand((int)time(0));
                    beeSpeed = (rand() % 200) + 200;
                    srand((int)time(0) * 10);
                    float height = (rand() %  inaltime / 2.16) + inaltime / 2.16;
                    spriteBee.setPosition(latime + 20, height);
                    beeActive = true;
                }
                else {
                    spriteBee.setPosition(
                                spriteBee.getPosition().x -
                                beeSpeed * dt.asSeconds(),
                                spriteBee.getPosition().y);
                    if (spriteBee.getPosition().x < -100) {
                        beeActive = false;
                    }
                }
                for (int i = 0; i < NUM_CLOUDS; ++i) {
                    clouds[i].move(dt);
                }
                std::stringstream ss;
                ss << "Score = " << score;
                scoreM.setString(ss.str());
                if (score > highScore)
                    highScore = score;
                std::stringstream sh;
                sh << "HighScore = " << highScore;
                highScoreM.setString(sh.str());
            }
            for (int i = 0; i < NUM_BRANCHES; ++i) {
                float height = i * 150;
                if (branchPositions[i] == side::LEFT) {
                    branches[i].setPosition(610, height);
                    branches[i].setRotation(180);
                } else if (branchPositions[i] == side::RIGHT) {
                    branches[i].setPosition(1330, height);
                    branches[i].setRotation(0);
                } else {
                    branches[i].setPosition(3000, height);
                }
            }
            if (logActive) {
                spriteLog.setPosition(spriteLog.getPosition().x +
                                      (logSpeedX * dt.asSeconds()),
                                      spriteLog.getPosition().y +
                                      logSpeedY * dt.asSeconds());
                if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x > 2000) {
                    logActive = false;
                    spriteLog.setPosition(810, 720);
                }
            }
            if (branchPositions[5] == playerSide) {
                notPlayed = true;
                acceptInput = false;
                if (playerSide == side::RIGHT) {
                    spriteRip.setPosition(1200, 760);
                    spriteAxe.setPosition(AXE_POSITION_RIGHT + 140, 900);
                } else {
                    spriteRip.setPosition(580, 760);
                    spriteAxe.setPosition(AXE_POSITION_LEFT - 140, 900);
                }

                spritePlayer.setPosition(2000, 660);

                play.setString("GAME OVER!");

                rect = play.getLocalBounds();

                play.setOrigin(rect.left +
                               rect.width / 2.0f,
                               rect.top +
                               rect.height / 2.0f);
                play.setPosition(1920 / 2.0f, 1080 / 2.0f);
                rip.play();
            }
            if (paused)
                window.draw(pause); ///PAUZA
        }

        if (notPlayed)
            window.draw(play); ///PRESS ENTER TO START sau OUT OF TIME
        window.display(); ///AFISAREA DESENELOR
    }
    return 0;
}
