#include "Men.h"
#include<iostream>
void Men::init(Chess* chess) {
	this->chess = chess;
}
void Men::go() {
	MOUSEMSG msg;
	ChessPos pos;
	//获取鼠标点击消息
	

	//通过chess对象，来调用 判断落子是否有效，以及落子功能
	while (true) {
		msg = GetMouseMsg();
         if (msg.uMsg == WM_LBUTTONDOWN &&
			 chess->clickBoard(msg.x, msg.y, &pos)) {
			 break;
	     }
	}
	chess->chessDown(&pos, CHESS_BLACK);
	
}