#include "Chess.h"
#include<mmsystem.h>
#include<math.h>
#pragma comment(lib,"winmm.lib")

// 只去掉图片周围的白色背景，不影响棋子本身
void putimagePNG(int x, int y, IMAGE* pImg, bool isBlack)
{
    DWORD* pBuffer = GetImageBuffer();
    DWORD* pSrc = GetImageBuffer(pImg);

    int w = pImg->getwidth();
    int h = pImg->getheight();
    int gw = getwidth();
    int gh = getheight();

    // 棋子中心区域（只判断外围为白色才透明，中心不判断）
    int cx = w / 2;
    int cy = h / 2;
    int safeR = w * 0.35;  // 中心安全区，不做透明判断

    for (int iy = 0; iy < h; iy++)
    {
        for (int ix = 0; ix < w; ix++)
        {
            DWORD c = pSrc[ix + iy * w];

            BYTE r = GetRValue(c);
            BYTE g = GetGValue(c);
            BYTE b = GetBValue(c);

            bool isWhite = (r > 240 && g > 240 && b > 240);

            // 如果是白色 + 不在棋子中心 → 跳过（透明）
            if (isWhite)
            {
                int dx = ix - cx;
                int dy = iy - cy;
                int distSq = dx * dx + dy * dy;

                if (distSq > safeR * safeR)
                    continue;
            }

            // 画
            int rx = x + ix;
            int ry = y + iy;
            if (rx >= 0 && rx < gw && ry >= 0 && ry < gh)
            {
                pBuffer[rx + ry * gw] = c;
            }
        }
    }
}
Chess::Chess(int gradeSize, int margin_x, int margin_y, float chesssize)
{
	this->gradeSize = gradeSize;
	this->margin_x = margin_x;
	this->margin_y = margin_y;
	this->chessSize = chesssize;
	playerflag = CHESS_BLACK;

	for (int i = 0; i < gradeSize; ++i) {
		vector<int>row;
		for (int j = 0; j < gradeSize; ++j) {
			row.push_back(0);
		}
		chessmap.push_back(row);
	}
   
}

void Chess::init()
{
	//创建游戏窗口
	initgraph(750, 748.327,EW_SHOWCONSOLE);//897 895

	//显示我们的棋盘图片
	loadimage(0, "棋盘3.jpg");
	//播放开始提示音
	//mcisendstring("")

	//加载黑棋和白棋棋子的图片
	loadimage(&chessBlackImg, "黑棋.png", chessSize, chessSize, true);
	loadimage(&chessWhiteImg, "白棋.png", chessSize, chessSize, true);

	//清理棋盘
	for (int i = 0; i < gradeSize; ++i) {
		for (int j = 0; j < gradeSize; ++j) {
			chessmap[i][j] = 0;
		}
	}
	playerflag=true;
}

bool Chess::clickBoard(int x, int y, ChessPos* pos)
{
    int col = (x - margin_x) / chessSize;
    int row = (y - margin_y) / chessSize; // 这里原代码写的是margin_x，应该是margin_y

    // 计算当前格子的四个角坐标
    int lefttopposx = margin_x + chessSize * col;
    int lefttopposy = margin_y + chessSize * row;
    int righttopposx = lefttopposx + chessSize;
    int righttopposy = lefttopposy;
    int leftbottomposx = lefttopposx;
    int leftbottomposy = lefttopposy + chessSize;
    int rightbottomposx = lefttopposx + chessSize;
    int rightbottomposy = lefttopposy + chessSize;

    int offset = chessSize * 0.4;
    bool ret = false;

    // 四个角的距离判断
    do {
        // 左上角
        int len_tl = sqrt((x - lefttopposx) * (x - lefttopposx) +
            (y - lefttopposy) * (y - lefttopposy));
        if (len_tl < offset) {
            pos->row = row;
            pos->col = col;
            break;
        }

        // 右上角
        int len_tr = sqrt((x - righttopposx) * (x - righttopposx) +
            (y - righttopposy) * (y - righttopposy));
        if (len_tr < offset) {
            pos->row = row;
            pos->col = col + 1;
            break;
        }

        // 左下角
        int len_bl = sqrt((x - leftbottomposx) * (x - leftbottomposx) +
            (y - leftbottomposy) * (y - leftbottomposy));
        if (len_bl < offset) {
            pos->row = row + 1;
            pos->col = col;
            break;
        }

        // 右下角
        int len_br = sqrt((x - rightbottomposx) * (x - rightbottomposx) +
            (y - rightbottomposy) * (y - rightbottomposy));
        if (len_br < offset) {
            pos->row = row + 1;
            pos->col = col + 1;
            break;
        }

        // 如果四个角都没命中，ret保持false
        return ret;
    } while (0);

    // 检查目标位置是否为空
    if (chessmap[pos->row][pos->col] == 0) {
        ret = true;
    }

    return ret;
}

void Chess::chessDown(ChessPos* pos, chess_kind_t kind)
{
    int x = margin_x + chessSize * pos->col - 0.5 * chessSize;
    int y = margin_y + chessSize * pos->row - 0.5 * chessSize;

    if (kind == CHESS_WHITE) {
        putimagePNG(x, y, &chessWhiteImg,false);
    }
    else { 
        putimagePNG(x, y, &chessBlackImg,true);
    }
    updategamemap(pos);
}

int Chess::getchessdata(int row,int col) {
    return chessmap[row][col];
}

int Chess::getGradeSize()
{

	return gradeSize;
}

bool Chess::checkOver()
{
	return false;
}

void Chess::updategamemap(ChessPos* pos) {
    chessmap[pos->row][pos->col] = playerflag ? CHESS_BLACK : CHESS_WHITE;
    playerflag = !playerflag;
}
