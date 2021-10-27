#include <sstream>
#include <SFML/Graphics.hpp>

using namespace sf;

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

int main()
{
    int latime = 1920;
    int inaltime = 1080;
    VideoMode vm(latime, inaltime);
    RenderWindow window(vm, "Timber", Style::Fullscreen);

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
    ///NORI
    Texture textureCloud;
    textureCloud.loadFromFile("graphics/cloud.png");
    ///CRENGI
    Texture textureBranch;
    textureBranch.loadFromFile("graphics/branch.png");

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
    ///NORI
    Sprite spriteCloud0;
    Sprite spriteCloud1;
    Sprite spriteCloud2;
    spriteCloud0.setTexture(textureCloud);
    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud0.setPosition(0, 0);
    spriteCloud1.setPosition(0, 250);
    spriteCloud2.setPosition(0, 500);
    bool cloud0active = false;
    bool cloud1active = false;
    bool cloud2active = false;
    float cloud0speed = 0.0f;
    float cloud1speed = 0.0f;
    float cloud2speed = 0.0f;
    ///CRENGI
    for (int i = 0; i < NUM_BRANCHES; ++i) {
        branches[i].setTexture(textureBranch);
        branches[i].setPosition(-2000, -2000);

        branches[i].setOrigin(220, 20);
    }
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

    updateBranches(1);
    updateBranches(2);
    updateBranches(3);
    updateBranches(4);
    updateBranches(5);

    /*
    ******************************
             BUCLA WHILE
    ******************************
    */
    while (window.isOpen()) {
        window.clear();
        window.draw(spriteBackground);
        window.draw(spriteCloud0);
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        for (int i = 0; i < NUM_BRANCHES; ++i) {
            window.draw(branches[i]);
        }
        window.draw(spriteTree);
        window.draw(spriteBee);
        window.draw(scoreM);
        window.draw(highScoreM);
        window.draw(timeBar);
        Time dt = clock.restart();
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::P)) {
            paused = !paused;
            while(Keyboard::isKeyPressed(Keyboard::P));
        }
        if (notPlayed == true)
            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                notPlayed = false;
                score = 0;
                timeRemaining = 6;
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
                if (!cloud0active) {
                    srand((int)time(0) * 10);
                    cloud0speed = (rand() % 200);
                    srand((int)time(0) * 10);
                    float height = rand() % 150;
                    spriteCloud0.setPosition(-200, height);
                    cloud0active = true;
                } else {
                    spriteCloud0.setPosition(
                                spriteCloud0.getPosition().x +
                                (cloud0speed * dt.asSeconds()),
                                spriteCloud0.getPosition().y);
                    if (spriteCloud0.getPosition().x > latime) {
                        cloud0active = false;
                    }
                }
                if (!cloud1active) {
                    srand((int)time(0) * 20);
                    cloud1speed = (rand() % 200);
                    srand((int)time(0) * 20);
                    float height = rand() % 300 - 150;
                    spriteCloud1.setPosition(-200, height);
                    cloud1active = true;
                } else {
                    spriteCloud1.setPosition(
                                spriteCloud1.getPosition().x +
                                (cloud1speed * dt.asSeconds()),
                                spriteCloud1.getPosition().y);
                    if(spriteCloud1.getPosition().x > latime) {
                        cloud1active = false;
                    }
                }
                if (!cloud2active) {
                    srand((int)time(0) * 30);
                    cloud2speed = (rand() % 200);
                    srand((int)time(0) * 30);
                    float height = rand() % 450 - 150;
                    spriteCloud2.setPosition(-200, height);
                    cloud2active = true;
                } else {
                    spriteCloud2.setPosition(
                                spriteCloud2.getPosition().x +
                                cloud2speed * dt.asSeconds(),
                                spriteCloud2.getPosition().y);
                    if (spriteCloud2.getPosition().x > latime) {
                        cloud2active = false;
                    }
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
            if (paused)
                window.draw(pause);
        }

        if (notPlayed)
            window.draw(play);
        window.display();
    }
    return 0;
}
