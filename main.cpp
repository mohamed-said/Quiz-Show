//#include "stdafx.h" // only for visual studio
#include <iostream>
#include <sstream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>
#include <conio.h>
#include <ctype.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define ESCAPE 27

using namespace std;

string QF = "q.qsf", AF = "a.qsf", QFT = "qt.qsf", AFT = "at.qsf", HSF = "hs.qsf";
vector<string> choices(4, "");
string rightAnswer = "", userName = "No Name";
int controller = 6, skip = 0, score = 0, ax, ay = 15, bx, by = 15, cx, cy = 18, dx, dy = 18;

string toStr(int);
void gotoxy(int, int);
void coutc(int, string);
void fileCopy(string, string);
void deleteLine(string, string);

void gameON();
void getAnswer(int);
void getQuestion(int);
void waiting();
void nextQuestion();
void wrongAnswer();
int getBalance(int);
bool isNewScore();

void menuLogo();
void menu();
void questBords();
void ansBords();
void borders();
void gameLogo();

int main() {

	system("TITLE Quiz Show Game");
	fileCopy(QF, QFT);
	fileCopy(AF, AFT);

	gameON();

	remove(QFT.c_str());
	remove(AFT.c_str());

	return 0;
}




void fileCopy(string original, string copy) {

	ifstream ifs(original.c_str(), ios::binary);
	ofstream ofs(copy.c_str(), ios::binary);
	ofs << ifs.rdbuf();
	return;
}

void deleteLine(string line, string file) {

	ifstream input;
	ofstream output;
	string temp;

	input.open(file.c_str());
	output.open((file + "temp").c_str());

	while(getline(input, temp)) {
		if(temp != line) {
			output << temp;
			if(!input.eof()) {
				output << endl;
			}
		}
	}
	input.close();
	output.close();
	remove(file.c_str());
	temp = file + "temp";
	rename(temp.c_str(), file.c_str());
	return;
}

string toStr(int x) {
	stringstream s;
	string temp;
	s << x;
	s >> temp;
	return temp;
}

void gameON() {

	system("CLS");
	srand((unsigned)time(0));
	int x = (rand() % controller) + skip;
	char m;
	borders();
	gameLogo();
	questBords();
	ansBords();
	getQuestion(x);
	getAnswer(x);

	gotoxy(1, 23);
	coutc(9, "Your Current Balance Is : ");
	gotoxy(27, 23);
	coutc(15, toStr(getBalance(score)));
	gotoxy(0, 24);

	while((m = _getch())) {

		if(toupper(m) == 'A') {
			gotoxy(ax, ay);
			coutc(14, choices[0]);
			waiting();
			if(choices[0] == rightAnswer) {
				gotoxy(ax, ay);
				coutc(10, choices[0]);
				nextQuestion();
				return;
			}else {
				gotoxy(ax, ay);
				coutc(12, choices[0]);
				wrongAnswer();
				return;
			}
		}else if(toupper(m) == 'B') {
			gotoxy(bx, by);
			coutc(14, choices[1]);
			waiting();
			if(choices[1] == rightAnswer) {
				gotoxy(bx, by);
				coutc(10, choices[1]);
				nextQuestion();
				return;
			}else {
				gotoxy(bx, by);
				coutc(12, choices[1]);
				wrongAnswer();
				return;
			}
		}else if(toupper(m) == 'C') {
			gotoxy(cx, cy);
			coutc(14, choices[2]);
			waiting();
			if(choices[2] == rightAnswer) {
				gotoxy(cx, cy);
				coutc(10, choices[2]);
				nextQuestion();
				return;
			}else {
				gotoxy(cx, cy);
				coutc(12, choices[2]);
				wrongAnswer();
				return;
			}
		}else if(toupper(m) == 'D') {
			gotoxy(dx, dy);
			coutc(14, choices[3]);
			waiting();
			if(choices[3] == rightAnswer) {
				gotoxy(dx, dy);
				coutc(10, choices[3]);
				nextQuestion();
				return;
			}else {
				gotoxy(dx, dy);
				coutc(12, choices[3]);
				wrongAnswer();
				return;
			}
		}else if(m == ESCAPE) {
			break;
		}
		gotoxy(0, 0);
	}

	return;
}

void getQuestion(int line) {

	string question;
	ifstream file;
	int i = -1;
	file.open(QFT.c_str());
	if(file.is_open()) {
		while(file.good() && i < line) {
			getline(file, question);
			i++;
		}
		file.close();
	}
	deleteLine(question, QFT);
	gotoxy(15 + ((50 - question.size()) / 2), 10);
	coutc(15, question);
	return;
}

void getAnswer(int line) {

	string answers;
	ifstream file;
	int i = -1, r = 0;

	file.open(AFT.c_str());
	if(file.is_open()) {
		while(file.good() && i < line) {
			getline(file, answers);
			i++;
		}
		file.close();
	}
	deleteLine(answers, AFT);
	choices[0] = answers.substr(1, answers.find("]", 0) - 1);
	rightAnswer = choices[0];
	r = answers.find("]", 0);
	choices[1] = answers.substr(answers.find("[", 2) + 1, answers.find("]", r + 1) - answers.find("[", 2) - 1);
	r = answers.find("]", r + 1);
	choices[2] = answers.substr(answers.find("[", r) + 1, answers.find("]", r + 1) - answers.find("[", r) - 1);
	r = answers.find("]", r + 1);
	choices[3] = answers.substr(answers.find("[", r) + 1, answers.find("]", r + 1) - answers.find("[", r) - 1);

	random_shuffle(choices.begin(), choices.end());

	ax = ((22 - choices[0].size()) / 2) + 9;
	bx = ((22 - choices[1].size()) / 2) + 52;
	cx = ((22 - choices[2].size()) / 2) + 9;
	dx = ((22 - choices[3].size()) / 2) + 52;

	gotoxy(ax, ay);
	coutc(15, choices[0]);
	gotoxy(bx, by);
	coutc(15, choices[1]);
	gotoxy(cx, cy);
	coutc(15, choices[2]);
	gotoxy(dx, dy);
	coutc(15, choices[3]);
	gotoxy(0, 24);
	return;
}

void nextQuestion() {

	score++;
	controller--;

	if(score == 5) {
		controller = 50;
		skip = 45;
	}else if(score == 10) {
		controller = 50;
		skip = 90;
	}

	if(score == 15) {
		//2afelha ebn el la3eeba :D
		return;
	}

	Sleep(1000);
	system("CLS");
	borders();
	gameLogo();
	gotoxy(5, 10);

	cout << "Eshta Right Answer";
	gotoxy(5, 11);
	cout << "Your Current Balance Is: " << getBalance(score);
	Sleep(2000);
	gameON();
	return;
}

void wrongAnswer() {

	Sleep(1000);
	system("CLS");
	gotoxy(0, 0);
	for (int i = 0; i <= 79; i++) coutc(15, "#");
	for(int i = 1; i <= 7; i++) {
		gotoxy(0, i);
		coutc(15, "#");
		gotoxy(79, i);
		coutc(15, "#");
	}
	gotoxy(0, 8);
	for (int i = 0; i <= 79; i++) coutc(15, "#");

	gotoxy(6, 2);
	coutc(15, "####    ####   ##   ##  ######          ####   ##  ##  ######  #####");
	gotoxy(5, 3);
	coutc(15, "##      ##  ##  ### ###  ##             ##  ##  ##  ##  ##      ##  ##");
	gotoxy(5, 4);
	coutc(15, "## ###  ######  ## # ##  ####           ##  ##  ##  ##  ####    #####");
	gotoxy(5, 5);
	coutc(15, "##  ##  ##  ##  ##   ##  ##             ##  ##   ####   ##      ##  ##");
	gotoxy(6, 6);
	coutc(15, "####   ##  ##  ##   ##  ######          ####     ##    ######  ##  ##");
	gotoxy(0, 10);

	if(isNewScore()) {
		cout << "You Scored a new high score: " << getBalance(score) << endl;
	}else {
		cout << "Your score: " << getBalance(score) << endl;
	}

	return;
}

bool isNewScore() {

	bool newscore = false;
	int r, nscore;
	string lines, user;
	ifstream hs;
	vector<pair<string, int> > hsData;
	hsData.resize(0);
	hs.open(HSF.c_str());

	while(hs.good() && !hs.eof()) {
		getline(hs, lines);
		user = lines.substr(1, lines.find("]", 0) - 1);
		r = lines.find("]", 0);
		nscore = atoi(lines.substr(lines.find("[", 2) + 1, lines.find("]", r + 1) - lines.find("[", 2) - 1).c_str());
		hsData.push_back(make_pair(user, nscore));
	}

	for(unsigned int i = 0; i < hsData.size(); i++) {
		if(hsData[i].second < getBalance(score)) {
			newscore = true;
			hsData.insert(hsData.begin() + i, make_pair(userName, getBalance(score)));
			hsData.pop_back();
			break;
		}
	}
	hs.close();
	if(newscore) {
		ofstream out;
		out.open(HSF.c_str());
		if(out.good()) {
			for(unsigned int i = 0; i < hsData.size(); i++) {
				out << '[' << hsData[i].first << "] [" << hsData[i].second << ']';
				if(i < hsData.size() - 1) {
					out << endl;
				}
			}
		}
		out.close();
	}

	return newscore;
}

int getBalance(int x) {

	int s;
	switch(x) {
	case 1:
		s = 100;
		break;
	case 2:
		s = 200;
		break;
	case 3:
		s = 300;
		break;
	case 4:
		s = 500;
		break;
	case 5:
		s = 1000;
		break;
	case 6:
		s = 2000;
		break;
	case 7:
		s = 4000;
		break;
	case 8:
		s = 8000;
		break;
	case 9:
		s = 16000;
		break;
	case 10:
		s = 32000;
		break;
	case 11:
		s = 64000;
		break;
	case 12:
		s = 125000;
		break;
	case 13:
		s = 250000;
		break;
	case 14:
		s = 500000;
		break;
	case 15:
		s = 1000000;
		break;
	default:
		s = 0;
		break;
	}

	return s;
}

void waiting() {

	gotoxy(69, 8);	coutc(15, "@@@@@@");
	gotoxy(73, 9);	coutc(15, "@@!");
	gotoxy(70, 10);	coutc(15, "@!!!:");
	gotoxy(73, 11);	coutc(15, "!!:");
	gotoxy(69, 12);	coutc(15, "::: ::");
	Sleep(1000);
	for(int i = 8; i < 13; i++) {
		gotoxy(68, i);
		for(int j = 0; j < 8; j++)
			coutc(15, " ");
	}
	gotoxy(69, 8);	coutc(15, "@@@@@@");
	gotoxy(68, 9);	coutc(15, "@@   @@@");
	gotoxy(70, 10);	coutc(15, ".!!@!");
	gotoxy(69, 11);	coutc(15, "!!:");
	gotoxy(68, 12);	coutc(15, ":.:: :::");
	Sleep(1000);
	for(int i = 8; i < 13; i++) {
		gotoxy(68, i);
		for(int j = 0; j < 8; j++)
			coutc(15, " ");
	}
	gotoxy(71, 8);	coutc(15, "@@@");
	gotoxy(70, 9);	coutc(15, "@@@@");
	gotoxy(71, 10);	coutc(15, "!@!");
	gotoxy(71, 11);	coutc(15, "!!!");
	gotoxy(71, 12);	coutc(15, "::");
	Sleep(1000);
	for(int i = 8; i < 13; i++) {
		gotoxy(68, i);
		for(int j = 0; j < 8; j++)
			coutc(15, " ");
	}
	return;
}

void menuLogo() {

	coutc(15, "################################################################################");
	coutc(15, "#    _______  __   __  ___   _______     _______  __   __  _______  _     _    #");
	coutc(15, "#   |       ||  | |  ||   | |       |   |       ||  | |  ||       || | _ | |   #");
	coutc(15, "#   |   _   ||  | |  ||   | |____   |   |  _____||  |_|  ||   _   || || || |   #");
	coutc(15, "#   |  | |  ||  |_|  ||   |  ____|  |   | |_____ |       ||  | |  ||       |   #");
	coutc(15, "#   |  |_|  ||       ||   | | ______|   |_____  ||       ||  |_|  ||       |   #");
	coutc(15, "#   |      | |       ||   | | |_____     _____| ||   _   ||       ||   _   |   #");
	coutc(15, "#   |____||_||_______||___| |_______|   |_______||__| |__||_______||__| |__|   #");
	coutc(15, "#                                                                              #");
	coutc(15, "################################################################################");
	return;
}

void menu() {

	menuLogo();
	gotoxy(33, 12);
	coutc(15, "Main Menu");
	gotoxy(33, 14);
	coutc(15, "Play Game");
	gotoxy(33, 15);
	coutc(15, "High Scores");
	gotoxy(33, 16);
	coutc(15, "About");
	gotoxy(33, 17);
	coutc(15, "Exit");

	char m;
	int op = 1;
	gotoxy(31, 13 + op);
	cout << "\4";
	gotoxy(0, 0);
	while((m = _getch())) {

		if(m == UP) {
			gotoxy(31, 13 + op);
			coutc(15, " ");
			if(op == 1) {
				op = 4;
			}else {
				op--;
			}
			gotoxy(31, 13 + op);
			coutc(15, "\4");
			gotoxy(0, 0);
		}else if(m == DOWN) {
			gotoxy(31, 13 + op);
			coutc(15, " ");
			if(op == 4) {
				op = 1;
			}else {
				op++;
			}
			gotoxy(31, 13 + op);
			coutc(15, "\4");
			gotoxy(0, 0);
		}else if(m == ENTER) {

			if(op == 1) {
				// start game
			}else if(op == 2) {
				// high scores page
			}else if(op == 3) {
				// about page
			}else if(op == 4) {
				break;
			}
		}else if(m == ESCAPE) {
			break;
		}
	}

	return;
}

void questBords() {

	gotoxy(17, 8);
	for (int i = 0; i <= 45; i++) coutc(15, "*");
	gotoxy(16, 9);	coutc(15, "*");
	gotoxy(15, 10);	coutc(15, "*");
	gotoxy(16, 11);	coutc(15, "*");
	gotoxy(17, 12);
	for (int i = 0; i <= 45; i++) coutc(15, "*");
	gotoxy(63, 9);	coutc(15, "*");
	gotoxy(64, 10);	coutc(15, "*");
	gotoxy(63, 11);	coutc(15, "*");

	return;
}

void ansBords() {

	// Answer A
	gotoxy(6, 14);
	for (int i = 0; i < 25; i++) coutc(15, "*");
	gotoxy(5, 15);	coutc(15, "*");
	gotoxy(7, 15);	coutc(15, "a - ");
	gotoxy(31, 15);	coutc(15, "*");
	gotoxy(6, 16);
	for (int i = 0; i < 25; i++) coutc(15, "*");

	// Answer B
	gotoxy(49, 14);
	for (int i = 1; i <= 25; i++) coutc(15, "*");
	gotoxy(48, 15);	coutc(15, "*");
	gotoxy(50, 15); coutc(15, "b - ");
	gotoxy(74, 15);	coutc(15, "*");
	gotoxy(49, 16);
	for (int i = 0; i < 25; i++) coutc(15, "*");

	// Answer C
	gotoxy(6, 17);
	for (int i = 0; i < 25; i++) coutc(15, "*");
	gotoxy(5, 18);	coutc(15, "*");
	gotoxy(7, 18);	coutc(15, "c - ");
	gotoxy(31, 18);	coutc(15, "*");
	gotoxy(6, 19);
	for (int i = 0; i < 25; i++) coutc(15, "*");

	// Answer D
	gotoxy(49, 17);
	for (int i = 1; i <= 25; i++) coutc(15, "*");
	gotoxy(48, 18);	coutc(15, "*");
	gotoxy(50, 18); coutc(15, "d - ");
	gotoxy(74, 18);	coutc(15, "*");
	gotoxy(49, 19);
	for (int i = 0; i < 25; i++) coutc(15, "*");

	return;
}

void borders() {

	for (int i = 0; i <= 79; i++) coutc(15, "#");
	for(int i = 1; i <= 20; i++) {
		gotoxy(0, i);
		coutc(15, "#");
		gotoxy(79, i);
		coutc(15, "#");
	}
	gotoxy(0, 21);
	for (int i = 0; i <= 79; i++) coutc(15, "#");

	return;
}

void gameLogo() {

	gotoxy(10, 1);
	coutc(15, "QQQQQ          iii           SSSSS  hh");
	gotoxy(9, 2);
	coutc(15, "QQ   QQ uu   uu     zzzzz    SS      hh       oooo  ww      ww");
	gotoxy(9, 3);
	coutc(15, "QQ   QQ uu   uu iii   zz      SSSSS  hhhhhh  oo  oo ww      ww");
	gotoxy(9, 4);
	coutc(15, "QQ  QQ  uu   uu iii  zz           SS hh   hh oo  oo  ww ww ww");
	gotoxy(10, 5);
	coutc(15, "QQQQ Q  uuuu u iii zzzzz     SSSSS  hh   hh  oooo    ww  ww");
	//gotoxy(0, 6);
	//for (int i = 0; i <= 79; i++) coutc(15, "#");

	return;
}
