#pragma once
#include"Men.h"
#include"AI.h"
#include"Chess.h"
class Chessgame
{
public:
	Chessgame(Men* man, AI* ai, Chess* chess);
	//开始对局
	void play();
//添加数据成员
private:
	Men* man;
	AI* ai;
	Chess* chess;

};

