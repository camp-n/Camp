#pragma once
#include<graphics.h>
#include<vector>
using namespace std;

//表示落子位置
struct ChessPos {
	int row;
	int col;

	ChessPos(int r=0,int c=0):row(r),col(c){}
};
typedef enum {
	CHESS_WHITE=-1,//白棋
	CHESS_BLACK=1
}chess_kind_t;
class Chess
{
public:
	Chess(int gradeSize, int margin_x, int margin_y, float chesssize);
	//棋盘的初始化
	void init();

	//检查落子位置是否正确

	bool clickBoard(int x, int y, ChessPos* pos);

	//下棋
	void chessDown(ChessPos* pos, chess_kind_t kind);

    //获取棋盘的大小（13，15，19）
	int getGradeSize();

	//获取棋盘位置是空、黑还是白
	int getchessdata(int row,int col);
	
	//检查游戏是否结束
	bool checkOver();

	//使用easyx图形库，来显示我们的棋盘，棋子

    void updategamemap(ChessPos*pos);

private:
	IMAGE chessBlackImg;//黑棋棋子
	IMAGE chessWhiteImg;//白棋棋子

	int gradeSize;  //棋盘大小
	float margin_x;   //棋盘的左侧边界
	float margin_y;   //棋盘的顶部边界
	float chessSize;  //棋子的大小

	//chessmap[3][5]表示棋盘的第3行第5列的落子情况 空：0   黑：1   白：-1
	vector<vector<int>>chessmap;

	//表示现在该谁下棋
	bool playerflag;  //true：该黑子走   false:该白子走

	
};

