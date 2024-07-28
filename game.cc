#include "game.h"
#include <string>
#include <iostream>
#include <sstream>
#include "types.h"
using namespace std;

Game::Game(): b{new Board()}, isWhite{1}, checkmate{false}, startGame{false}, p1{nullptr}, p2{nullptr}, p1Score{0}, p2Score{0}{}


void Game::endGame(char status){
    cout << *b << endl; // print the board

    if(status == 's'){
        cout << "The game is a draw!" << endl;
        p1Score += 0.5;
        p2Score += 0.5;
    }
    
    if(status == 'g'){
        if(isWhite){
            ++p1Score;
            cout << "Checkmate! White player won!" << endl;
        }
        else{
            ++p2Score;
            cout << "Checkmate! Black player won!" << endl;
        }
    }

    if(status == 'r'){
        if(isWhite){
            ++p1Score;
            cout << "Black Resigned! White player won!" << endl;
        }
        else{
            ++p2Score;
            cout << "White Resigned! Black player won!" << endl;
        }
    }

    delete b;
    b = new Board{};

    startGame = false;
    isWhite = 1;
}

// NEED TO IMPLEMENT THIS
// We need this because we put the different levels as inheritance instead in one class
// We can change this if we want
void ComputerDifficulty(int difficulty, Player* cp){
    if(difficulty == 1){
        cp = new Level1()
    }
    // unfinished
}


void Game::play(){
    string command, p1Type, p2Type;
    int difficulty;
    int needSetUp = 0;
    while(cin >> command){
        if(startGame == false && command == "game"){ // game white-player black-player
            if(needSetUp == 0){
                std::stringstream defaultSetUp;
                defaultSetUp << "+ r a8 + n b8 + b c8 + q d8 + k e8 + b f8 + n g8 + r h8 ";
                defaultSetUp << "+ p a7 + p b7 + p c7 + p d7 + p e7 + p f7 + p g7 + p h7 ";
                defaultSetUp << "+ P a2 + P b2 + P c2 + P d2 + P e2 + P f2 + P g2 + P h2 ";
                defaultSetUp << "+ R a1 + N b1 + B c1 + Q d1 + K e1 + B f1 + N g1 + R h1 ";
                defaultSetUp << "done ";
                b->commandIntepreter(defaultSetUp, 1);
            }
            cin >> p1Type >> p2Type;
            if(p1){ delete p1; }
            if(p2){ delete p2; }
            if(p1Type == "human"){
                p1 = new HumanPlayer{1}; // white
            }
            else{
                if(p1Type.back()-'0' < 1 || p1Type.back()-'0' > 4){
                    std::cout << "The computer difficulty needs to be in between 1-4 inclusive, difficulty default set to 1" << std::endl;
                    difficulty = 1;
                }else{
                    difficulty = p1Type.back() - '0';
                }
                ComputerDifficulty(difficulty, p1);
            }

            if(p2Type == "human"){
                p2 = new HumanPlayer{0}; // black
            }
            
            // CONTINUE HERE

    cout << "Final Score" << endl;
    cout << "White: " << p1Score << endl;
    cout << "Black: " << p2Score << endl;
}

Game::~Game(){
    delete b;
    delete p1;
    delete p2;
}
