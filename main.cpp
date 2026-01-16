#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cmath>
#include <ctime>
#include <fstream>
#define g 9.81
#define PI 3.14159265
#define BULLET_COLOR 6
#define TERRAIN_COLOR 10
#define TANK_COLOR 8
#define WIDTH 150
#define HEIGHT 34
struct Tanks;
int ground[WIDTH];
using namespace std;
//FUNCTION DECLARATIONS
//VOID
void printGameHeader();
void printTerrain();
void printTank(Tanks &player);
void generateColors(int k);
void deleteTank1();
void deleteTank2();
void hideCursor();
void testBullet();
void switchTurn();
void moveTanksRight(Tanks& tankToMove);
void moveTanksLeft(Tanks& tankToMove);
void setHealth(Tanks &healthToPrint,int decrement);
void deleteTank(const Tanks& tankToDelete);
void MainMenu(int &Choice);
void gotoxy(int x, int y);
void setGameControls();
void printColoredWord(const string& text, int colorCode);
void increaseAngle(Tanks& angleToIncrease);
void decreaseAngle(Tanks& angleToIncrease);
void printAngle(const Tanks& angleToPrint);
void drawAim(Tanks &player);
void deleteAngle(const Tanks& angleToDelete);
void increaseVelocity(Tanks& velocityToIncrease);
void decreaseVelocity(Tanks& velocityToDecrease);
void printVelocity(const Tanks& velocityToPrint);
void checkWinner(const Tanks &oppTank,bool &run);
void printFuel(const Tanks& fuelToPrint);
void deleteFuel(const Tanks& fuelToPrint);
void printGameControls();
void drawBox(const int x,const int y,const int width,const int height,const string& title);
void deleteVelocity(const Tanks& velocityToDelete);
void getSettings(int &Choice);
void bulletPlayer(Tanks& player);
void blowAnimation(int x,int y);
void printGameControls(int selected);
void setFullScreen();
void clearInputBuffer();
void printMenu(string menu[],int rows,int selected);
int getMainChoice(int &choice,string s[],int rows);
void saveGame();
void loadGame();
bool hasSavedGame();
void saveControls();
void loadControls();
//DOUBLE
float projectileHeight(double angle,double velocity);
float projectileRange(double angle,double velocity);
float projectileTime(double angle,double velocity);
//OTHERS
char getCharAtXY(short int x,short int y );
double toRadians(double angleInDegrees);
string GetKeyName(int vkCode);
//structs
struct Tanks {
    int x;
    int y;
    int id;
    int bulletX;
    int bulletY;
    float angle;
    float velocity;
    float fuel;
    int health;
    string top;
    string dlt;
    int aimX[5];
    int aimY[5];
};
struct Controls {
    int moveLeft = VK_LEFT;
    int moveRight = VK_RIGHT;
    int incAngle = VK_UP;
    int decAngle = VK_DOWN;
    int incVel = 'W';
    int decVel = 'S';
    int fire = 'F';
    int mainMenu = VK_ESCAPE;
};
Controls control;
Tanks player1 = {
    .x = 22,
    .y = 13,
    .id = 0,
    .bulletX = 0,
    .bulletY = 0,
    .angle = 0,
    .velocity = 0,
    .fuel = 15,
    .health = 100,
    .top = " ---> ",
    .dlt = "      "
};
Tanks player2 = {
    .x = 124,
    .y = 13,
    .id = 1,
    .bulletX = 0,
    .bulletY = 0,
    .angle = 0,
    .velocity = 0,
    .fuel =15,
    .health = 100,
    .top = " <--- ",
    .dlt = "      ",
};
Tanks *currentPlayer = &player1;
Tanks *enemyTank = &player2;
int main() {
    setFullScreen();
    SetConsoleOutputCP(CP_UTF8);
    hideCursor();
    loadControls();
    int mainChoice = 0;
    bool gameRunning = false;
    bool rightShiftWasDown = false;
    while (mainChoice != 2 ) {
        printGameHeader();
        MainMenu(mainChoice);
        if (mainChoice == 0) {
            gameRunning = true;
            printTerrain();
            printTank(player1);
            printTank(player2);
            printAngle(*currentPlayer);
            printVelocity(*currentPlayer);
            printFuel(*currentPlayer);
            drawAim(*currentPlayer);
            setHealth(player1,0);
            setHealth(player2,0);
            while (gameRunning) {
                if (GetAsyncKeyState(control.mainMenu)) {
                    saveGame();
                    gameRunning = false;
                }
                if (GetAsyncKeyState(control.moveRight)) {
                    moveTanksRight(*currentPlayer);
                }
                if (GetAsyncKeyState(control.moveLeft)) {
                    moveTanksLeft(*currentPlayer);
                }
                if (GetAsyncKeyState(control.incAngle)) {
                    increaseAngle(*currentPlayer);
                }
                if (GetAsyncKeyState(control.decAngle)) {
                    decreaseAngle(*currentPlayer);
                }
                if (GetAsyncKeyState(control.incVel)) {
                    increaseVelocity(*currentPlayer);
                }
                if (GetAsyncKeyState(control.decVel)) {
                    decreaseVelocity(*currentPlayer);
                }
                if (GetAsyncKeyState(control.fire)) {
                    bulletPlayer(*currentPlayer);
                    checkWinner(*enemyTank,gameRunning);
                    switchTurn();
                }
                Sleep(30);
            }
        }else if (mainChoice == 1) {
            if (hasSavedGame()) {
                loadGame();
                gameRunning = true;
                printTerrain();
                printTank(player1);
                printTank(player2);
                printAngle(*currentPlayer);
                printVelocity(*currentPlayer);
                printFuel(*currentPlayer);
                drawAim(*currentPlayer);
                setHealth(player1,0);
                setHealth(player2,0);
                while (gameRunning) {
                    if (GetAsyncKeyState(control.mainMenu)) {
                        saveGame();
                        gameRunning = false;
                    }
                    if (GetAsyncKeyState(control.moveRight)) {
                        moveTanksRight(*currentPlayer);
                    }
                    if (GetAsyncKeyState(control.moveLeft)) {
                        moveTanksLeft(*currentPlayer);
                    }
                    if (GetAsyncKeyState(control.incAngle)) {
                        increaseAngle(*currentPlayer);
                    }
                    if (GetAsyncKeyState(control.decAngle)) {
                        decreaseAngle(*currentPlayer);
                    }
                    if (GetAsyncKeyState(control.incVel)) {
                        increaseVelocity(*currentPlayer);
                    }
                    if (GetAsyncKeyState(control.decVel)) {
                        decreaseVelocity(*currentPlayer);
                    }
                    if (GetAsyncKeyState(control.fire)) {
                        bulletPlayer(*currentPlayer);
                        checkWinner(*enemyTank,gameRunning);
                        switchTurn();
                    }
                    Sleep(30);
                }
            } else {
                printGameControls(0);
            }
        }else if (mainChoice == 3) {
            printGameControls(0);
        }
    }
    return 0;
}
void drawSideTank() {
    generateColors(8);
    int startY = 19;

    string tank[] = {
        "███████████████████████▄          ",
        "▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓███▄        ",
        "███████████████████████████▄      ",
        "  ▀██████████████████████████▄    ",
        "    ▀██████████████████████████▄  ",
        "  ▄██████████████████████████████ ",
        " █▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█",
        " █  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  █",
        " ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀ "
    };
    string rightTank[] = {
        "          ▄███████████████████████",
        "        ▄███▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓",
        "      ▄███████████████████████████",
        "    ▄██████████████████████████▀  ",
        "  ▄██████████████████████████▀    ",
        " ██████████████████████████████▄  ",
        "█▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀█ ",
        "█  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  ▄▀▀▄  █ ",
        "▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀  ▀▄▄▀ "
    };
    for (int i = 0; i < 9; i++) {
        gotoxy(2, startY + i);
        if (i < 3) generateColors(7);
        else generateColors(8);
        cout << tank[i];
    }
    int rightEdge = WIDTH - 35;
    for (int i = 0; i < 9; i++) {
        gotoxy(rightEdge, startY + i);
        generateColors(i < 3 ? 7 : 8);
        cout << rightTank[i];
    }
}
void saveControls() {
    fstream file;
    file.open("controls.txt", ios::out);
    if (file.is_open()) {
        file << control.moveRight << " "
             << control.moveLeft << " "
             << control.incAngle << " "
             << control.decAngle << " "
             << control.incVel << " "
             << control.decVel << " "
             << control.fire;
        file.close();
    }
}
void loadControls() {
    fstream file;
    file.open("controls.txt", ios::in);
    if (file.is_open()) {
        file >> control.moveRight >> control.moveLeft >> control.incAngle
             >> control.decAngle >> control.incVel >> control.decVel >> control.fire;
        file.close();
    }
}
void setGameControls() {
    string ControlTitles[] = {"MOVE RIGHT","MOVE LEFT","INCREASE ANGLE","DECREASE ANGLE","INCREASE POWER","DECREASE POWER","FIRE","SAVE & EXIT"};
    int choice = 0;
    while (true) {
        getMainChoice(choice, ControlTitles, 8);
        if (choice == 7) {
            saveControls();
            break;
        }
        gotoxy(57, 33);
        printColoredWord("PRESS NEW KEY...", 13);
        clearInputBuffer();
        bool keyPressed = false;
        int newKey = 0;
        while (!keyPressed) {
            for (int vk = 8; vk <= 255; vk++) {
                if (GetAsyncKeyState(vk) & 0x8000) {
                    newKey = vk;
                    keyPressed = true;
                    break;
                }
            }
            Sleep(10);
        }
        switch(choice) {
            case 0: control.moveRight = newKey; break;
            case 1: control.moveLeft = newKey; break;
            case 2: control.incAngle = newKey; break;
            case 3: control.decAngle = newKey; break;
            case 4: control.incVel = newKey; break;
            case 5: control.decVel = newKey; break;
            case 6: control.fire = newKey; break;
        }
        Sleep(300);
        printGameControls(choice);
    }
}
void clearStage() {
    for (int i = 15; i < 25; i++) {
        for (int j= 55 ; j < 75; j++) {
            gotoxy(j, i);
            cout << " ";
        }
    }
}
void clearInputBuffer() {
    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    FlushConsoleInputBuffer(hStdIn);
    while (_kbhit()) {_getch();}
    fflush(stdin);
}
string GetKeyName(int vkCode) {
    char name[64];

    // 1. Get the Scan Code from the Virtual Key
    UINT scanCode = MapVirtualKey(vkCode, MAPVK_VK_TO_VSC);

    // 2. Prepare the lParam for GetKeyNameText
    // We shift the scan code and handle "Extended Keys" (Arrows, etc.)
    LONG lParam = scanCode << 16;

    // Extended keys bit (bit 24) must be set for Arrows, Home, Delete, etc.
    if (vkCode >= 0x21 && vkCode <= 0x2E) lParam |= (1 << 24); // PageUp to Delete
    if (vkCode >= 0x25 && vkCode <= 0x28) lParam |= (1 << 24); // Arrow keys

    // 3. Get the String name
    if (GetKeyNameTextA(lParam, name, sizeof(name)) > 0) {
        return std::string(name);
    }

    // 4. Fallback for simple letters if the API fails
    if (vkCode >= 0x30 && vkCode <= 0x5A) {
        return std::string(1, (char)vkCode);
    }

    return "Unknown Key";
}
void drawAim(Tanks &player) {
    int startX;
    if (player.id == 0) {
        player.bulletX = player.x + 2;
        startX = player.x + 6;
    }else if (player.id == 1) {
        player.bulletX = player.x - 1;
        startX = player.x;
    }
    player.bulletY = player.y;
    int startY = player.bulletY;
    double y = 0;
    double x = 0;
    float i = 0;
    for (int j = 0; j < 5; j++) {
        y = startY-(player.velocity)*sin(toRadians(player.angle))*i + (0.5*g*i*i);
        player.aimY[j] = (round(y));
        x = player.velocity*cos(toRadians(player.angle))*i;
        if (player.id == 0) {
            player.aimX[j] = startX + round(x);
        }else if (player.id == 1) {
            player.aimX[j] = startX - round(x);
        }
        if (player.aimY[j] < ground[player.aimX[j]] && player.aimY[j] < enemyTank->x) {
            gotoxy(player.aimX[j], player.aimY[j]);
            cout << "*";
        }
        i += 0.3;
    }
    // printTank(*enemyTank);
}
void deleteAim(Tanks &player) {
    for (int j = 0; j < 5; j++) {
        if (player.aimY[j] < ground[player.aimX[j]]) {
            gotoxy(player.aimX[j], player.aimY[j]);
            cout << " ";
        }
    }
}
int getMainChoice(int &choice,string s[], const int rows) {
    while (true) {
        if (GetAsyncKeyState(VK_UP)) {
            if (choice > 0) {
                choice--;
                printMenu(s,rows,choice);
            }
        }
        if (GetAsyncKeyState(VK_DOWN)) {
            if (choice < rows-1) {
                choice++;
                printMenu(s,rows,choice);
            }
        }
        if (GetAsyncKeyState('F')) {
            return 0;
        }
        Sleep(150);
    }
}
void printMenu(string menu[], const int rows, const int selected) {
    int x = 60;
    int y = 15;
    generateColors(10);
    for (int i = 0 ; i < rows ; i++) {
        gotoxy(x,y);
        if (i == selected) {
            printColoredWord("→"+menu[i],95);
        }else {
            printColoredWord(menu[i]+" ",10);
        }
        y += 2;
    }
}
void switchTurn() {
    if (currentPlayer == &player1) {
        currentPlayer = &player2;
        enemyTank = &player1;
        deleteAngle(player1);
        deleteVelocity(player1);
        deleteFuel(player1);
        player1.fuel = 15;
        printAngle(player2);
        printVelocity(player2);
        printFuel(player2);
        drawAim(player2);
    }else if (currentPlayer == &player2) {
        currentPlayer = &player1;
        enemyTank = &player2;
        deleteAngle(player2);
        deleteVelocity(player2);
        deleteFuel(player2);
        player2.fuel = 15;
        printAngle(player1);
        printVelocity(player1);
        printFuel(player1);
        drawAim(player1);
    }
}
void getSettings(int &Choice) {
    string s[] = {"CONTROL SETTINGS", "GAMEPLAY SETTINGS","SAVE"};
    printMenu(s,3,0);
    drawSideTank();
    getMainChoice(Choice,s,3);
}
void drawBox(const int x,const int y,const int width,const int height,const string& title) {
    generateColors(11);
    gotoxy(x, y);
    cout << "╔";
    for (int i = 0; i < width - 2; i++) cout << "═";
    cout << "╗";
    for (int i = 1; i < height; i++) {
        gotoxy(x, y + i); cout << "║";
        gotoxy(x + width - 1, y + i); cout << "║";
    }
    gotoxy(x, y + height);
    cout << "╚";
    for (int i = 0; i < width - 2; i++) cout << "═";
    cout << "╝";
    int titlePos = x + (width / 2) - (title.length() / 2);
    gotoxy(titlePos, y);
    generateColors(143);
    cout << " " << title << " ";
}
void printGameControls(int selected){
    int X = 57;
    int Y = 14;
    clearStage();
    drawBox(X,Y,30,18,"CONTROL SETTINGS");
    string ControlTitles[] = {"MOVE RIGHT","MOVE LEFT","INCREASE ANGLE","DECREASE ANGLE","INCREASE POWER","DECREASE POWER","FIRE","SAVE & MAIN MENU"};
    generateColors(10);
    printMenu(ControlTitles,sizeof(ControlTitles)/sizeof(string),selected);
    string KeyName[7] = {GetKeyName(control.moveRight),GetKeyName(control.moveLeft),GetKeyName(control.incAngle),GetKeyName(control.decAngle),GetKeyName(control.incVel),GetKeyName(control.decVel),GetKeyName(control.fire)};
    Y = 15;
    generateColors(14);
    for (const string & i : KeyName) {
        gotoxy(X+18,Y);
        cout << i;
        Y+=2;
    }
    setGameControls();
}
void MainMenu(int &Choice) {
    if (hasSavedGame()) {
        string s[] = {"NEW GAME","RESUME","EXIT","KEYS SETTINGS"};
        printMenu(s,4,0);
        drawSideTank();
        getMainChoice(Choice,s,4);
    } else {
        string s[] = {"PLAY","KEYS SETTINGS","EXIT"};
        printMenu(s,3,0);
        drawSideTank();
        getMainChoice(Choice,s,3);
    }
}
void printPlayer1Winner() {
    string s[] = {
        "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗      ██╗██╗    ██╗██╗███╗   ██╗███████╗",
        "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ███║██║    ██║██║████╗  ██║██╔════╝",
        "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝    ╚██║██║ █╗ ██║██║██╔██╗ ██║███████╗",
        "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗     ██║██║███╗██║██║██║╚██╗██║╚════██║",
        "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║     ██║╚███╔███╔╝██║██║ ╚████║███████║",
        "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝     ╚═╝ ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝"
    };
    int y = 11;
    for (int i = 0; i < 6; i++) {
        generateColors(i);
        gotoxy(32,y+i);
        cout << s[i];
    }
}
void printPlayer2Winner() {
    string s[] = {
        "██████╗ ██╗      █████╗ ██╗   ██╗███████╗██████╗     ██████╗ ██╗    ██╗██╗███╗   ██╗███████╗",
        "██╔══██╗██║     ██╔══██╗╚██╗ ██╔╝██╔════╝██╔══██╗    ╚════██╗██║    ██║██║████╗  ██║██╔════╝",
        "██████╔╝██║     ███████║ ╚████╔╝ █████╗  ██████╔╝     █████╔╝██║ █╗ ██║██║██╔██╗ ██║███████╗",
        "██╔═══╝ ██║     ██╔══██║  ╚██╔╝  ██╔══╝  ██╔══██╗    ██╔═══╝ ██║███╗██║██║██║╚██╗██║╚════██║",
        "██║     ███████╗██║  ██║   ██║   ███████╗██║  ██║    ███████╗╚███╔███╔╝██║██║ ╚████║███████║",
        "╚═╝     ╚══════╝╚═╝  ╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝    ╚══════╝ ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚══════╝"
    };
    int y = 11;
    for (int i = 0; i < 6; i++) {
        generateColors(i);
        gotoxy(32,y+i);
        cout << s[i];
    }
}
void checkWinner(const Tanks &oppTank,bool &run) {
    if (oppTank.health <= 0) {
        if (oppTank.id == 1) {
            printPlayer1Winner();
        }else {
            printPlayer2Winner();
        }
        run = false;
    }
}
void blowAnimation(int x,int y) {
    generateColors(15);
    gotoxy(x, y); cout << "█";
    Sleep(40);
    generateColors(14);
    gotoxy(x - 1, y);     cout << "▄█▀";
    gotoxy(x - 1, y - 1); cout << "▀█▄";
    Sleep(60);
    generateColors(12);
    gotoxy(x - 1, y);     cout << "   ";
    gotoxy(x - 1, y - 1); cout << "   ";
    gotoxy(x - 2, y + 1); cout << " ◢██◣ ";
    gotoxy(x - 2, y);     cout << "██████";
    gotoxy(x - 2, y - 1); cout << " ◥██◤ ";
    Beep(200, 50);
    Sleep(80);
    generateColors(8);
    gotoxy(x - 2, y + 1); cout << " ░░░░ ";
    gotoxy(x - 2, y);     cout << "░░░░░░";
    gotoxy(x - 2, y - 1); cout << " ░░░░ ";
    Sleep(100);
    gotoxy(x - 2, y + 1); cout << "      ";
    gotoxy(x - 2, y);     cout << "      ";
    gotoxy(x - 2, y - 1); cout << "      ";
}
void checkDamage(const Tanks &player,Tanks &enemyTank) {
    int r = 10;
    if (player.id == 0) {
        r = player.bulletX-enemyTank.x;
    }else if (player.id == 1) {
        r = enemyTank.x-player.bulletX;
    }
    if (r > -5 && r < 5 ) {
        setHealth(enemyTank,10);
    }else if (r > -9 && r < 9) {
        setHealth(enemyTank,5);
    }
    printTank(enemyTank);
    printTank(*currentPlayer);
}
void createCrater(int craterX) {
    generateColors(TERRAIN_COLOR);
    int radius = 6;

    for (int i = -radius; i <= radius; i++) {
        int targetX = craterX + i;

        // 1. Boundary Check: Don't go off the left/right of the screen
        if (targetX >= WIDTH || targetX < 0) continue;

        // 2. Smooth Depth Calculation
        double verticalOffset = sqrt(pow(radius, 2) - pow(i, 2));
        int depth = (int)(verticalOffset * 0.7);

        // 3. THE CLAMP: Prevent ground from going below the screen floor
        // If ground + depth is more than HEIGHT-1, we cap it at HEIGHT-1
        if (ground[targetX] + depth >= HEIGHT) {
            ground[targetX] = HEIGHT - 1;
        } else {
            ground[targetX] += depth;
        }

        // 4. Safe Drawing
        for(int y = ground[targetX] - 10; y < HEIGHT; y++) {
            // Safety: Never gotoxy outside the console buffer
            int safeY = (y < 0) ? 0 : (y >= HEIGHT ? HEIGHT - 1 : y);

            gotoxy(targetX, safeY);

            if (safeY < ground[targetX]) cout << " ";
            else if (safeY == ground[targetX]) cout << "█";
            else cout << "▒";
        }
    }
}
void bulletPlayer(Tanks &player) {
    Beep(500,100);
    int startX;
    if (player.id == 0) {
        player.bulletX = player.x + 7;
        startX = player.x + 6;
    }else if (player.id == 1) {
        player.bulletX = player.x - 1;
        startX = player.x;
    }
    player.bulletY = player.y;
    int startY = player.bulletY;
    double y = 0;
    double x = 0;
    float i = 0;
    while (true) {
        y = startY-(player.velocity)*sin(toRadians(player.angle))*i + (0.5*g*i*i);
        player.bulletY = (round(y));
        x = player.velocity*cos(toRadians(player.angle))*i;
        if (player.id == 0) {
            player.bulletX = startX + round(x);
        }else if (player.id == 1) {
            player.bulletX = startX - round(x);
        }
        if (player.bulletX < 0 || player.bulletX > WIDTH) {
            break;
        }
        if (ground[player.bulletX] < player.bulletY) {
            Beep(150,300);
            blowAnimation(player.bulletX,player.bulletY);
            createCrater(player.bulletX);
            break;
        }
        // if (getCharAtXY(player.bulletX,player.bulletY+1)!=' ') {
        //     blowAnimation(player.bulletX,player.bulletY);
        //     createCrater(player.bulletX);
        //     break;
        // }
        if (getCharAtXY(player.bulletX+1,player.bulletY)!=' ') {
            blowAnimation(player.bulletX,player.bulletY);
            createCrater(player.bulletX);
            break;
        }
        if (player.bulletY > 0) {
            gotoxy(player.bulletX, player.bulletY);
            cout << "●";
            Sleep(40);
            gotoxy(player.bulletX, player.bulletY);
            cout << " ";
        }
        i += 0.15;
        Sleep(7);
    }
    checkDamage(*currentPlayer,*enemyTank);

    deleteAim(*currentPlayer);

}
void moveTanksRight(Tanks& tankToMove) {
    if (tankToMove.x + 8 < WIDTH && tankToMove.fuel > 0) {
        tankToMove.fuel --;
        deleteAim(*currentPlayer);
        deleteTank(tankToMove);
        deleteFuel(tankToMove);
        tankToMove.x ++;
        printTank(tankToMove);
        drawAim(*currentPlayer);
        printFuel(tankToMove);
    }
}
void moveTanksLeft(Tanks& tankToMove) {
    if (tankToMove.x > 0 && tankToMove.fuel > 0) {
        tankToMove.fuel --;
        deleteAim(*currentPlayer);
        deleteTank(tankToMove);
        deleteFuel(tankToMove);
        tankToMove.x --;
        printTank(tankToMove);
        drawAim(*currentPlayer);
        printFuel(tankToMove);
    }
}
void deleteTank(const Tanks& tankToDelete) {
    if (tankToDelete.id == 0) {
        deleteTank1();
    }else if (tankToDelete.id == 1) {
        deleteTank2();
    }
}
void setHealth(Tanks &healthToPrint, const int decrement) {
    healthToPrint.health -= decrement;
    int hX=1;
    int hY=1;
    if (healthToPrint.id == 0) {
        hX = 1;
    }else if (healthToPrint.id == 1) {
        hX = WIDTH - 29;
    }
    gotoxy(hX,hY);
    for (int i = 0; i< 29;i++) {
        cout << " ";
    }
    gotoxy(hX,hY);
    generateColors(14);
    cout << "HEALTH: ";
    int i =0;
    while (i <= healthToPrint.health) {
        if (i > 0 && i < 30) {
            generateColors(4);
            cout << "█";
        }
        else if (i >= 30 && i < 60) {
            generateColors(6);
            cout << "█";
        }
        if (i >= 60 && i <=100) {
            generateColors(10);
            cout << "█";
        }
        i += 5;
    }
}
void increaseAngle(Tanks &angleToIncrease) {
    deleteAim(*currentPlayer);
    if (angleToIncrease.angle < 85) {
        angleToIncrease.angle += 0.5;
        printAngle(angleToIncrease);
    }
    drawAim(*currentPlayer);
}
void decreaseAngle(Tanks &angleToIncrease) {
    deleteAim(*currentPlayer);
    if (angleToIncrease.angle > 0) {
        angleToIncrease.angle -= 0.5;
        printAngle(angleToIncrease);
    }
    drawAim(*currentPlayer);
}
void printAngle(const Tanks& angleToPrint) {
    generateColors(14);
    if (angleToPrint.id == 0) {
        gotoxy(1,2);
        cout << "Angle : ";
    }else if (angleToPrint.id == 1) {
        gotoxy(121,2);
        cout << "Angle : ";
    }
    generateColors(7);
    cout <<angleToPrint.angle;
}
void deleteAngle(const Tanks& angleToDelete) {
    if (angleToDelete.id == 0) {
        gotoxy(1,2);
        cout << "            ";
    }else if (angleToDelete.id == 1) {
        gotoxy(121,2);
        cout << "            ";
    }
}
void increaseVelocity(Tanks &velocityToIncrease) {
    deleteAim(*currentPlayer);
    if (velocityToIncrease.velocity < 44.5) {
        velocityToIncrease.velocity += 0.5;
        deleteVelocity(velocityToIncrease);
        printVelocity(velocityToIncrease);
    }
    drawAim(*currentPlayer);
}
void decreaseVelocity(Tanks &velocityToDecrease) {
    deleteAim(*currentPlayer);
    if (velocityToDecrease.velocity > 0.5) {
        velocityToDecrease.velocity -= 0.5;
        deleteVelocity(velocityToDecrease);
        printVelocity(velocityToDecrease);
    }
    drawAim(*currentPlayer);
}
void printVelocity(const Tanks& velocityToPrint) {
    generateColors(14);
    if (velocityToPrint.id == 0) {
        gotoxy(1,3);
        cout << "Power : ";
    }else if (velocityToPrint.id == 1) {
        gotoxy(121,3);
        cout << "Power : ";
    }
    generateColors(7);
    int i = 0;
    while (i < velocityToPrint.velocity) {
        cout << "█";
        i += 5;
    }
}
void printFuel(const Tanks& fuelToPrint) {
    generateColors(14);
    if (fuelToPrint.id == 0) {
        gotoxy(1,4);
        cout << "Fuel : ";
    }else if (fuelToPrint.id == 1) {
        gotoxy(121,4);
        cout << "Fuel : ";
    }
    generateColors(6);
    int i = 0;
    while (i <= fuelToPrint.fuel) {
        cout << "█";
        i += 1;
    }
}
void deleteFuel(const Tanks& fuelToPrint) {
    if (fuelToPrint.id == 0) {
        gotoxy(1,4);
        cout << "                       ";
    }else if (fuelToPrint.id == 1) {
        gotoxy(121,4);
        cout << "                       ";
    }
}
void deleteVelocity(const Tanks& velocityToDelete) {
    if (velocityToDelete.id == 0) {
        gotoxy(1,3);
        cout << "                 ";
    }else if (velocityToDelete.id == 1) {
        gotoxy(121,3);
        cout << "                 ";
    }
}
void printGameHeader() {system("cls");
    system("cls");
    generateColors(6);
    int x = 35;
    int y = 1;
    string tankLogo[] = {
        "████████╗ █████╗ ███╗   ██╗██╗  ██╗    ██╗    ██╗ █████╗ ██████╗ ",
        "╚══██╔══╝██╔══██╗████╗  ██║██║ ██╔╝    ██║    ██║██╔══██╗██╔══██╗",
        "   ██║   ███████║██╔██╗ ██║█████╔╝     ██║ █╗ ██║███████║██████╔╝",
        "   ██║   ██╔══██║██║╚██╗██║██╔═██╗     ██║███╗██║██╔══██║██╔══██╗",
        "   ██║   ██║  ██║██║ ╚████║██║  ██╗    ╚███╔███╔╝██║  ██║██║  ██║",
        "   ╚═╝   ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝     ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝"
    };
    for (int i = 0; i < 6; i++) {
        gotoxy(x, y + i);
        cout << tankLogo[i];
    }
    generateColors(8);
    gotoxy(0, y + 7);
    for(int i = 0; i < 149; i++) cout << "━";
    generateColors(12);
    gotoxy(x + 15, y + 8);
    cout << "  [ ▓]  BATTLEFIELD COMMAND CENTER  [ ▓ ]  ";
    generateColors(8);
    gotoxy(0, y + 9);
    for(int i = 0; i < 149; i++) cout << "━";
    generateColors(7);
    cout << endl;
}
void printTank(Tanks &player) {
    player.y = ground[player.x+3]-3;
        string upBarrelP1[] = {" ", " ", "/", "/", " ", " ", " "};
        string downBarrelP1[]   = {" ", " ", "\\", "\\", " ", " ", " "};
        string flatBarrelP1[] = {" ", " ", "=", "=", " ", " ", " "};
        string upBarrelP2[] = {" ", " ", " ", "\\", "\\", " ", " "};
        string downBarrelP2[]   = {" ", " ", " ", "/", "/", " ", " "};
        string flatBarrelP2[] = {" ", " ", " ", "=", "=", " ", " "};
    generateColors(8);
    bool tiltedUp = false;
    bool tiltedDown = false;
    int coord[7];
    for ( int i = 0 ; i < 7; i ++) {
        int currentX = player.x+i;
        int currentY = ground[player.x+i]-1;
        coord[i] = currentY;
        gotoxy(currentX,currentY);
        if (i == 3) player.y = currentY - 2;
        cout << "▒";
    }
    if ((coord[0]+coord[1])/2-(coord[5]+coord[6])/2>2) {
        tiltedUp = true;
    }else if ((coord[0]+coord[1])/2-(coord[5]+coord[6])/2<-2) {
        tiltedDown = true;
    }
    string flatTurret[] = {" ", "▄", "█", "▀", "█", "▄", " "};
    string upTurret[]   = {" ", "▟", "█", "█", "█", "▀", " "};
    string downTurret[] = {" ", "▀", "█", "█", "█", "▙", " "};
    string* activeTurret = flatTurret;
    string* activeBarrel;
    if (player.id == 0) {
        if (tiltedUp) {activeTurret = upTurret;activeBarrel = upBarrelP1;}
        else if (tiltedDown) {activeTurret = downTurret;activeBarrel = downBarrelP1;}
        else {activeTurret = flatTurret;activeBarrel = flatBarrelP1;}
    }else if (player.id == 1) {
        if (tiltedUp) {activeTurret = upTurret;activeBarrel = upBarrelP2;}
        else if (tiltedDown) {activeTurret = downTurret;activeBarrel = downBarrelP2;}
        else {activeTurret = flatTurret;activeBarrel = flatBarrelP2;}
    }
    for (int i = 0; i < 7; i++) {
        gotoxy(player.x + i, ground[player.x + i] - 2);
        cout << activeTurret[i];
        gotoxy(player.x + i, ground[player.x + i] - 3);
        cout << activeBarrel[i];
    }
    generateColors(7);
}
void deleteTank1() {
    string s = "       ";
    for ( int i = 0 ; i < 7; i ++) {
        gotoxy(player1.x+i,ground[player1.x+i]-1);
        cout << s[i];
    }
}
void deleteTank2() {
    string s = "       ";
    for ( int i = 0 ; i < 7; i ++) {
        gotoxy(player2.x+i,ground[player2.x+i]-1);
        cout << s[i];
    }
}
void generateTerrain(float seed) {
    int baseline = 25;
    int amplitude = 4;
    for (int x = 0; x < WIDTH; x++) {
        double y = baseline +
                   (amplitude * sin((x *seed)* 0.1)) +
                   ((amplitude / 2.0) * cos(x * 0.3));

        ground[x] = (int)y;
    }

}
void printTerrain() {
    system("cls");
    generateColors(TERRAIN_COLOR);
    float seed[] = {0.5,0.7,0.9,1.1,1.3,1.5,1.7,1.9,2.1,2.3,2.5};
    srand(time(NULL));
    int fseed = seed[rand()%11];
    generateTerrain(fseed);
    for (int x = 0; x < WIDTH; x++) {
        for (int y = ground[x]; y < HEIGHT; y++) {
            gotoxy(x, y);
            if (y == ground[x]) cout << "█";
            else cout << "▒";
        }
    }

}
void generateColors(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, k);
}
void gotoxy(const int x, const int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Set the cursor visibility to false
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}
void printColoredWord(const string& text, int colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD savedAttributes = consoleInfo.wAttributes;
    SetConsoleTextAttribute(hConsole, colorCode);
    cout << text;
    SetConsoleTextAttribute(hConsole, savedAttributes);
}
double toRadians(const double angleInDegrees) {
    return angleInDegrees * (PI / 180.0);
}
float projectileHeight(const double angle,const double velocity) {
    double Radian = toRadians(angle);
    return (((velocity*velocity)*(sin(Radian)*sin(Radian)))/(2*g));
}
float projectileRange(const double angle, const double velocity) {
    double Radian = toRadians(angle);
    return (((velocity*velocity)*(sin(2*Radian)))/(g));
}
float projectileTime(const double angle, const double velocity) {
    double Radian = toRadians(angle);
    return (((2*velocity)*(sin(Radian)))/g);
}
char getCharAtXY(short int x,short int y ) {
    CHAR_INFO ci;
    COORD xy = {0,0};
    SMALL_RECT sr = {x,y,x,y};
    COORD coordBuffSize = {1,1};
    return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE),&ci,coordBuffSize,xy,&sr)? ci.Char.AsciiChar:' ';
}
void setFullScreen() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE);
}
void saveGame() {
    fstream file;
    file.open("savegame.dat", ios::out | ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<char*>(&player1), sizeof(Tanks));
        file.write(reinterpret_cast<char*>(&player2), sizeof(Tanks));
        int currentPlayerID = currentPlayer->id;
        file.write(reinterpret_cast<char*>(&currentPlayerID), sizeof(int));
        file.write(reinterpret_cast<char*>(ground), sizeof(ground));
        file.close();
    }
}
void loadGame() {
    fstream file;
    file.open("savegame.dat", ios::in | ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&player1), sizeof(Tanks));
        file.read(reinterpret_cast<char*>(&player2), sizeof(Tanks));
        int currentPlayerID;
        file.read(reinterpret_cast<char*>(&currentPlayerID), sizeof(int));
        if (currentPlayerID == 0) {
            currentPlayer = &player1;
            enemyTank = &player2;
        } else {
            currentPlayer = &player2;
            enemyTank = &player1;
        }
        file.read(reinterpret_cast<char*>(ground), sizeof(ground));
        file.close();
    }
}
bool hasSavedGame() {
    fstream file;
    file.open("savegame.dat", ios::in | ios::binary);
    bool exists = file.is_open();
    if (exists) {
        file.close();
    }
    return exists;
}