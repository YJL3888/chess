#include "game.h"

#include <iostream>
#include <sstream>
#include <string>

#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "types.h"
using namespace std;

Game::Game()
    : b{new Board()},
      p1{nullptr},
      p2{nullptr},
      isWhite{true},
      checkmate{false},
      startGame{false},
      p1Score{0},
      p2Score{0} {}

void Game::endGame(char status) {
  cout << *b << endl;  // print the board

  if (status == 'd') {
    cout << "Stalemate! The game is a draw!" << endl;
    p1Score += 0.5;
    p2Score += 0.5;
  }

  if (status == 'w') {
    if (isWhite) {
      ++p1Score;
      cout << "Checkmate! White player won!" << endl;
    } else {
      ++p2Score;
      cout << "Checkmate! Black player won!" << endl;
    }
  }

  if (status == 'r') {
    if (isWhite) {
      ++p1Score;
      cout << "Black Resigned! White player won!" << endl;
    } else {
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
// We need this because we put the different levels as inheritance instead in
// one class We can change this if we want
Player* Game::ComputerDifficulty(int difficulty, bool isWhite) {
  Player* computerPlayer;
  switch (difficulty) {
    case 1:
      computerPlayer = new Level1(isWhite);
      break;
    case 2:
      computerPlayer = new Level2(isWhite);
      break;
    case 3:
      computerPlayer = new Level3(isWhite);
      break;
    case 4:
      computerPlayer = new Level4(isWhite);
      break;
    default:
      computerPlayer = new Level1(isWhite);
      break;
  }
  return computerPlayer;
}

void Game::play() {
  string command, p1Type, p2Type;
  int difficulty;
  int setUpMode = 0;
  string outputImage = "0";
  int printImage = 0;

  // option for graphical display
  std::cout << "Options for graphical display (Enter[0-2]): " << std::endl;
  std::cout << "0. No graphical display updates" << std::endl;
  std::cout << "1. Graphical display with strings/letters" << std::endl;
  std::cout << "2. Graphical display with images" << std::endl;
  while(cin >> outputImage){
    if(outputImage != "0" && outputImage != "1" && outputImage != "2"){
      std::cout << "Invalid input! You should enter 0, 1, or 2 :/" << std::endl;
    }else{
      if(outputImage == "0"){
        printImage = 0;
      }else if(outputImage == "1"){
        printImage = 1;
      }else{
        printImage = 2;
      }
      break;
    }
  }

  std::cout << std::endl;
  std::cout << "Options for bonus marks: " << std::endl;
  std::cout << "Bonus Marks +1000 " << std::endl;
  std::cout << std::endl;

  // // option to output images or the chess strings
  // std::cout << "Would you like to output the chess piece image? (yes/no)" << std::endl;
  // while(cin >> outputImage){
  //   if(outputImage != "yes" && outputImage != "no"){
  //     std::cout << "Invalid input! You should enter yes or no :/" << std::endl;
  //   }else{
  //     if(outputImage == "yes"){
  //       printImage = 1;
  //     }
  //     break;
  //   }
  // }
  // cout<< "You can enter your commands now :)" << endl;
  
  cout<< "You can enter your commands now :)" << endl;

  while (cin >> command) {
    // CASE WHEN NO ACTIVE GAME
    if (startGame == false && command == "game") {  // game white-player black-player
      if (setUpMode == 0) {
        stringstream defaultSetUp;
        defaultSetUp
            << "+ r a8 + n b8 + b c8 + q d8 + k e8 + b f8 + n g8 + r h8 ";
        defaultSetUp
            << "+ p a7 + p b7 + p c7 + p d7 + p e7 + p f7 + p g7 + p h7 ";
        defaultSetUp
            << "+ P a2 + P b2 + P c2 + P d2 + P e2 + P f2 + P g2 + P h2 ";
        defaultSetUp
            << "+ R a1 + N b1 + B c1 + Q d1 + K e1 + B f1 + N g1 + R h1 ";
        defaultSetUp << "done ";
        b->commandIntepreter(defaultSetUp, 0, printImage);
      }
      cin >> p1Type >> p2Type;
      // check if p1 and p2 contain existing players, delete if not null => give
      // space to create new players.
      if (p1) {
        delete p1;
      }
      if (p2) {
        delete p2;
      }
      // delete p1;
      // delete p2;

      if (p1Type == "human") {
        p1 = new HumanPlayer(true);
      }  // true means white
      else {
        if (p1Type.back() - '0' < 1 ||
            p1Type.back() - '0' > 4) {  // invalid computer level.
          cout << "Invalid level for player 1. The computer difficulty needs "
                  "to be in between 1-4 inclusive, difficulty default set to 1"
               << endl;
          difficulty = 1;
        } else {  // valid computer level.
          difficulty = p1Type.back() - '0';
        }
        // ComputerDifficulty(difficulty, p1, true);  // true means white
        p1 = ComputerDifficulty(difficulty, true);
      }

      if (p2Type == "human") {
        p2 = new HumanPlayer(false);
      }  // false means black
      else {
        if (p2Type.back() - '0' < 1 ||
            p2Type.back() - '0' > 4) {  // invalid computer level.
          cout << "Invalid level for player 2. The computer difficulty needs "
                  "to be in between 1-4 inclusive, difficulty default set to 1"
               << endl;
          difficulty = 1;
        } else {  // valid computer level.
          difficulty = p2Type.back() - '0';
        }
        // ComputerDifficulty(difficulty, p2, false);  // false means black
        p2 = ComputerDifficulty(difficulty, false);
      }

      // STARTING GAME!
      startGame = true;
      cout << *b << endl;
    }

    // CASE WHEN THERE IS ACTIVE GAME
    else if (startGame) {
      if (command == "move") {
        if (isWhite && p1->getPlayerType() == PlayerType::computer) {
          Move move = p1->getMove(b);
          totalMoves++;
          cout << "White computer made the move "
               << XlocationToChar(move.first.first) << move.first.second
               << " TO " << XlocationToChar(move.second.first)
               << move.second.second << endl;
          cout<< "Made " << totalMoves << " move(s) in total! Go Go!" << std::endl;
          if (move.second.second == -1) {  // Stalemate - draw
            endGame('d');
            continue;
          }
          if (move.second.second == -2) {  // checkmate - win
            endGame('w');
            continue;
          }
        }

        if (!isWhite && p2->getPlayerType() == PlayerType::computer) {
          Move move = p2->getMove(b);
          totalMoves++;
          cout << "Black computer made the move "
               << XlocationToChar(move.first.first) << move.first.second
               << " TO " << XlocationToChar(move.second.first)
               << move.second.second << endl;
          cout<< "Made " << totalMoves << " move(s) in total! Go Go!" << std::endl;

          if (move.second.second == -1) {  // Stalemate - draw
            endGame('d');
            continue;
          }
          if (move.second.second == -2) {  // checkmate - win
            endGame('w');
            continue;
          }
        }

        if (!isWhite && p2->getPlayerType() == PlayerType::human) {
          cout << "Human (black side) is making a move" << endl;
          Move move = p2->getMove(b);
          totalMoves++;
          cout<< "Made " << totalMoves << " move(s) in total! Go Go!" << std::endl;
          if (move.second.second == -1) {  // Stalemate - draw
            endGame('d');
            continue;
          }
          if (move.second.second == -2) {  // checkmate - win
            endGame('w');
            continue;
          }
        }

        if (isWhite && p1->getPlayerType() == PlayerType::human) {
          cout << "Human (white side)  is making a move" << endl;
          Move move = p1->getMove(b);
          totalMoves++;
          cout<< "Made " << totalMoves << " move(s) in total! Go Go!" << std::endl;
          if (move.second.second == -1) {  // Stalemate - draw
            endGame('d');
            continue;
          }
          if (move.second.second == -2) {  // checkmate - win
            endGame('w');
            continue;
          }
        }

        if (cin.eof()) {
          break;
        }
        cout << *b << endl;
        isWhite = !isWhite;
        isWhite ? cout << "White's turn" << endl
                : cout << "Black's turn" << endl;
      }

      if (command == "resign") {
        isWhite = !isWhite;
        endGame('r');
      }
      if (command == "setup") {
        cout << "No setting up allowed during a game!" << endl;
      }
      if (command == "game") {
        cout << "There is an active game in progress!" << endl;
      }
    }

    // moving
    else if (command == "move") {
      cout << "Invalid command. Game is not initalized yet!" << endl;
    } else if (command == "setup") {
      cout << "Would you like to display the setup everytime you modify the board? (yes/no)" << endl;
      string displaySetup = "no";
      bool printSetup = 0;
      while(cin >> displaySetup){
        if(displaySetup != "yes" && displaySetup != "no"){
          std::cout << "Invalid input! You should enter yes or no :/" << std::endl;
        }else{
          if(displaySetup == "yes"){
            printSetup = 1;
          }
          break;
        }
      }
      cout << "You can add your setup now :)" << std::endl;
      isWhite = b->commandIntepreter(cin, printSetup, printImage);
      setUpMode = 1;
    }
  }

  cout << "Final Score" << endl;
  cout << "White: " << p1Score << endl;
  cout << "Black: " << p2Score << endl;
}

Game::~Game() {
  delete b;
  delete p1;
  delete p2;
}
