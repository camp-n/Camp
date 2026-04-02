#include "AI.h"

void AI::init(Chess* chess)
{
	this->chess = chess;

	for (int i = 0; i < chess->getGradeSize(); ++i) {
		vector<int>row;
		for (int j = 0; j < chess->getGradeSize(); ++j) {
			row.push_back(0);
		}
		scoremap.push_back(row);
	}
}

void AI::go()
{
    ChessPos pos = think();
    Sleep(1000); //假装思考
    chess->chessDown(&pos, CHESS_WHITE);
}

void AI::calculatescore() {

    // 评分向量数组清零
    for (int i = 0; i < scoremap.size(); ++i) {
        for (int j = 0; j < scoremap[i].size(); ++j) {
            scoremap[i][j] = 0;
        }
    }

    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {   // 遍历整个棋盘
            if (chess->getchessdata(row, col))
                continue;

            for (int y = -1; y <= 1; y++) {
                for (int x = -1; x <= 1; x++) {    // 遍历八个方向
                    if (y == 0 && x == 0)
                        continue;

                    // ======================
                    // 按你的要求：变量放在这里！每个方向重新开始
                    // ======================
                    int personnum = 0;  // 棋手方连续棋子
                    int ainum = 0;      // ai方
                    int emptynum = 0;   // 该方向空白位个数

                    // 正方向
                    for (int i = 1; i <= 4; ++i) {
                        int currow = row + i * y;
                        int curcol = col + i * x;

                        if (currow >= 0 && currow < size && curcol >= 0 && curcol < size) {
                            int c = chess->getchessdata(currow, curcol);
                            if (c == 1) {
                                personnum++;
                            }
                            else if (c == 2) {
                                ainum++;
                            }
                            else if (c == 0) {
                                emptynum++;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }

                    // 反方向（左边2个+右边2个 靠这里累加）
                    for (int i = 1; i <= 4; ++i) {
                        int currow = row - i * y;
                        int curcol = col - i * x;

                        if (currow >= 0 && currow < size && curcol >= 0 && curcol < size) {
                            int c = chess->getchessdata(currow, curcol);
                            if (c == 1) {
                                personnum++;  // 累加
                            }
                            else if (c == 2) {
                                ainum++;     // 累加AI
                            }
                            else if (c == 0) {
                                emptynum++;
                                break;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            break;
                        }
                    }

                    // ======================
                    // 你的原有评分：堵玩家（防守）
                    // ======================
                    if (personnum == 1) {
                        scoremap[row][col] += 10;
                    }
                    else if (personnum == 2) {
                        if (emptynum == 1) {
                            scoremap[row][col] += 30;
                        }
                        else if (emptynum == 2) {
                            scoremap[row][col] += 40;
                        }
                    }
                    else if (personnum == 3) {
                        if (emptynum == 1) {
                            scoremap[row][col] += 60;
                        }
                        else if (emptynum == 2) {
                            scoremap[row][col] += 200;
                        }
                    }
                    else if (personnum == 4) {
                        scoremap[row][col] += 20000;
                    }

                    // ======================
                    // 新增：AI自己进攻评分（和你防守格式完全一样）
                    // ======================
                    if (ainum == 1) {
                        scoremap[row][col] += 15;
                    }
                    else if (ainum == 2) {
                        if (emptynum == 1) {
                            scoremap[row][col] += 35;
                        }
                        else if (emptynum == 2) {
                            scoremap[row][col] += 50;
                        }
                    }
                    else if (ainum == 3) {
                        if (emptynum == 1) {
                            scoremap[row][col] += 100;
                        }
                        else if (emptynum == 2) {
                            scoremap[row][col] += 300;
                        }
                    }
                    else if (ainum == 4) {
                        scoremap[row][col] += 50000; // AI能赢优先于堵人
                    }

                }
            }
        }
    }
}

ChessPos AI::think()   //寻找最佳位置下棋
{
    calculatescore();
    int maxscore = 0;
    vector<ChessPos>maxpoint;
    int size = chess->getGradeSize();
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            if (chess->getchessdata(row, col) == 0) {
                if (scoremap[row][col] > maxscore) {
                    maxscore = scoremap[row][col];
                    maxpoint.clear();
                    maxpoint.push_back(ChessPos(row, col));
                }
                else if (scoremap[row][col] == maxscore) {
                    maxpoint.push_back(ChessPos(row, col));
                }
            }
        }
    }

    int index = rand() % maxpoint.size();
    return maxpoint[index];
}
