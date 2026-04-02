#pragma once
#include"Chess.h"
#include<vector>
class AI
{
public:
	//AI的初始化
	void init(Chess*chess);
	//AI下棋
	void go();
private:
	Chess* chess;
	vector<vector<int>>scoremap;

	void calculatescore();
	ChessPos think();
};

