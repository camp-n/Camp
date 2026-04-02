#include "Chessgame.h"

Chessgame::Chessgame(Men* man, AI* ai, Chess* chess)
{
	this->man = man;
	this-> ai = ai;
	this->chess = chess;

	man->init(chess);
	ai->init(chess);
}

void Chessgame::play()
{
	chess->init();
	while (true) {
		//先有棋手走
		man->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}
		//由AI走
		ai->go();
		if (chess->checkOver()) {
			chess->init();
			continue;
		}

	}
}
