#include "game.h"

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <chrono>

#include "level1.h"
#include "level2.h"
#include "level3.h"
#include "level4.h"
#include "level5.h"
#include "types.h"
using namespace std;

Game::Game()
    : b{std::make_unique<Board>()},
      p1{nullptr},
      p2{nullptr},
      isWhite{true},
      checkmate{false},
      startGame{false},
      p1Score{0},
      p2Score{0},
      whiteTimeLeft{0},
      blackTimeLeft{0},
      timeControl{false}
{}

void Game::endGame(char status) {
  cout << *b << endl;  // print the board

  if (status == 'd') {
    cout << "Stalemate! The game is a draw!" << endl;
    cout << "Made " << totalMoves << " move(s) in total! Good Game!"
         << std::endl;
    p1Score += 0.5;
    p2Score += 0.5;
  }

  if (status == 'w') {
    if (isWhite) {
      ++p1Score;
      cout << "Checkmate! White player won!" << endl;
      cout << "Made " << totalMoves
           << " move(s) in total! Black player you are so close :("
           << std::endl;
    } else {
      ++p2Score;
      cout << "Checkmate! Black player won!" << endl;
      cout << "Made " << totalMoves
           << " move(s) in total! White player you are so close :("
           << std::endl;
    }
  }

  if (status == 'r') {
    if (isWhite) {
      ++p1Score;
      cout << "Black Resigned! White player won!" << endl;
      cout << "Made " << totalMoves
           << " move(s) in total! Can't believe black resigned :(" << std::endl;
    } else {
      ++p2Score;
      cout << "White Resigned! Black player won!" << endl;
      cout << "Made " << totalMoves
           << " move(s) in total! Can't believe white resigned :(" << std::endl;
    }
  }

  if (status == 't') {
    if (isWhite) {
      ++p2Score;
      cout << "White ran out of time! Black player won! Hurry up white player :/" << endl;
    } else {
      ++p1Score;
      cout << "Black ran out of time! White player won! Hurry up black player :/" << endl;
    }
  }

  b = std::make_unique<Board>();
  totalMoves = 0;

  startGame = false;
  isWhite = 1;
}

std::unique_ptr<Player> Game::ComputerDifficulty(int difficulty, bool isWhite) {
  std::unique_ptr<Player> computerPlayer;
  switch (difficulty) {
    case 1:
      computerPlayer = std::make_unique<Level1>(isWhite);
      break;
    case 2:
      computerPlayer = std::make_unique<Level2>(isWhite);
      break;
    case 3:
      computerPlayer = std::make_unique<Level3>(isWhite);
      break;
    case 4:
      computerPlayer = std::make_unique<Level4>(isWhite);
      break;
    case 5:
      computerPlayer = std::make_unique<Level5>(isWhite);
      break;
    default:
      computerPlayer = std::make_unique<Level1>(isWhite);
      break;
  }
  return computerPlayer;
}

void Game::startTimer() {
  startTime = std::chrono::steady_clock::now();
}

void Game::endTimer() {
  endTime = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
  if (isWhite) {
    whiteTimeLeft -= elapsed;
    if (whiteTimeLeft <= 0) {
      endGame('t');
      return;
    }
  } else {
    blackTimeLeft -= elapsed;
    if (blackTimeLeft <= 0) {
      endGame('t');
      return;
    }
  }
  displayTime();
}

void Game::displayTime() {
  cout << "White Time Left: " << whiteTimeLeft / 60 << " minutes " << whiteTimeLeft % 60 << " seconds" << endl;
  cout << "Black Time Left: " << blackTimeLeft / 60 << " minutes " << blackTimeLeft % 60 << " seconds" << endl;
  cout << "Time used for this move: " << chrono::duration_cast<chrono::seconds>(endTime - startTime).count() << " seconds" << endl;
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
  while (cin >> outputImage) {
    if (outputImage != "0" && outputImage != "1" && outputImage != "2") {
      std::cout << "Invalid input! You should enter 0, 1, or 2 :/" << std::endl;
    } else {
      if (outputImage == "0") {
        printImage = 0;
      } else if (outputImage == "1") {
        printImage = 1;
      } else {
        printImage = 2;
      }
      break;
    }
  }

  std::cout << std::endl;
  std::cout << "Options for bonus marks: " << std::endl;
  std::cout << "Bonus Marks +1000 " << std::endl;
  std::cout << std::endl;

  cout << "You can enter your commands now :)" << endl;

  while (cin >> command) {
    // CASE WHEN NO ACTIVE GAME
    if (startGame == false &&
        command == "game") {  // game white-player black-player
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
      p1.reset();
      p2.reset();

      if (p1Type == "human") {
        p1 = std::make_unique<HumanPlayer>(true);
      } else {
        if (p1Type.back() - '0' < 1 || p1Type.back() - '0' > 5) {
          cout << "Invalid level for player 1. The computer difficulty needs "
                  "to be in between 1-4 inclusive, difficulty default set to 1"
               << endl;
          difficulty = 1;
        } else {
          difficulty = p1Type.back() - '0';
        }
        p1 = ComputerDifficulty(difficulty, true);
      }

      if (p2Type == "human") {
        p2 = std::make_unique<HumanPlayer>(false);
      } else {
        if (p2Type.back() - '0' < 1 || p2Type.back() - '0' > 5) {
          cout << "Invalid level for player 2. The computer difficulty needs "
                  "to be in between 1-4 inclusive, difficulty default set to 1"
               << endl;
          difficulty = 1;
        } else {
          difficulty = p2Type.back() - '0';
        }
        p2 = ComputerDifficulty(difficulty, false);
      }

      // Time control option!!
      string timeControlOption = "no";
      timeControl = false;
      if(p1Type == "human" && p2Type == "human"){
        cout << "We have two human players! Would you like to have time control? (yes/no)" << endl;
        while(cin >> timeControlOption){
          if(timeControlOption != "yes" && timeControlOption != "no"){
            std::cout << "Invalid input! You should enter yes or no :/" << std::endl;
          }else{
            if(timeControlOption == "yes"){
              timeControl = true;
            }
            break;
          }
        }
      }

      if(timeControl){
        int minutes;
        cout << "Enter your time control in minutes: ";
        cin >> minutes;
        whiteTimeLeft = minutes * 60;
        blackTimeLeft = minutes * 60;
      }

      startGame = true;
      cout << *b << endl;
      if (timeControl) startTimer();
    }

    // CASE WHEN THERE IS ACTIVE GAME
    else if (startGame) {
      if (command == "move") {
        if (timeControl) endTimer();
        if (!startGame) continue; // If the game ended due to time out, skip processing the move

        if (isWhite && p1->getPlayerType() == PlayerType::computer) {
          Move move = p1->getMove(b.get());
          totalMoves++;
          cout << "White computer made the move "
               << XlocationToChar(move.first.first) << move.first.second
               << " TO " << XlocationToChar(move.second.first)
               << move.second.second << endl;
          cout << "Made " << totalMoves << " move(s) in total! Go Go!"
               << std::endl;
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
          Move move = p2->getMove(b.get());
          totalMoves++;
          cout << "Black computer made the move "
               << XlocationToChar(move.first.first) << move.first.second
               << " TO " << XlocationToChar(move.second.first)
               << move.second.second << endl;
          cout << "Made " << totalMoves << " move(s) in total! Go Go!"
               << std::endl;

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
          Move move = p2->getMove(b.get());
          totalMoves++;
          cout << "Made " << totalMoves << " move(s) in total! Go Go!"
               << std::endl;
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
          Move move = p1->getMove(b.get());
          totalMoves++;
          cout << "Made " << totalMoves << " move(s) in total! Go Go!"
               << std::endl;
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
        if (timeControl) startTimer();
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

    else if (command == "move") {
      cout << "Invalid command. Game is not initalized yet!" << endl;
    } else if (command == "setup") {
      cout << "Would you like to display the setup everytime you modify the "
              "board? (yes/no)"
           << endl;
      string displaySetup = "no";
      bool printSetup = 0;
      while (cin >> displaySetup) {
        if (displaySetup != "yes" && displaySetup != "no") {
          std::cout << "Invalid input! You should enter yes or no :/"
                    << std::endl;
        } else {
          if (displaySetup == "yes") {
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

Game::~Game() = default;
