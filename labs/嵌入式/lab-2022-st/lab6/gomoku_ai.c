#include "gomoku_ai.h"
#include "gomoku.h"
#include <stdlib.h>
#include <time.h>

const int INT_MAX = 0x7fffffff / 2;
const int INT_MIN = -0x7fffffff / 2;

struct Position {
  int x, y;
};

static int Around(int x, int y); // 周围是否有子存在，无子的就加入考虑
static int ScoreTable(int Number, int Empty); // 积分表
static int CountScore(int n[], int turn);      // 算单个数组分
static int Evaluate();
static int Max_AlphaBeta(int Dep, int alpha, int beta); // 轮到AI下子时，AI作的选择
static int Min_AlphaBeta(int Dep, int alpha, int beta); // 轮到对手下子时，对手作的选择


static int Map[BOARD_SIZE][BOARD_SIZE], win[2][2005];
static int ai_playertable[BOARD_SIZE][BOARD_SIZE][2005],
    OTtable[BOARD_SIZE][BOARD_SIZE][2005];
static int Start, Count;

static int ai_player = BLACK_CHESS;

int Around(int x, int y) // 空子只算旁边有子的
{
  int i, j;
  for (i = (x - 2 > 0 ? x - 2 : 0); i <= x + 2 && i < BOARD_SIZE; i++)
    for (j = (y - 2 > 0 ? y - 2 : 0); j <= y + 2 && j < BOARD_SIZE; j++)
      if (Map[i][j] != NO_CHESS)
        return 1;
  return 0;
}

/*
    按照成五 100000、活四 10000、活三 1000、活二 100、活一 10、死四 1000、死三
   100、死二 10 的规则给棋盘上的所有棋子打分， 然后把所有 AI
   和对手棋子的得分分别相加，ScoreME 为 AI 得分，ScoreOTHER 为对手得分， ScoreME
   - ScoreOTHER 即为当前局势的总分数
*/

int ScoreTable(int Number, int Empty) // 计分板
{
  if (Number >= 5)
    return 100000;
  else if (Number == 4) {
    if (Empty == 2)
      return 10000;
    else if (Empty == 1)
      return 1000;
  } else if (Number == 3) {
    if (Empty == 2)
      return 1000;
    else if (Empty == 1)
      return 100;
  } else if (Number == 2) {
    if (Empty == 2)
      return 100;
    else if (Empty == 1)
      return 10;
  } else if (Number == 1 && Empty == 2)
    return 10;
  return 0;
}

int CountScore(int n[],
               int turn) // 正斜线、反斜线、横、竖，均转成一维数组来计算
{
  int Scoretmp = 0, L = n[0], Empty = 0, Number = 0;
  if (n[1] == 0)
    Empty++;
  else if (n[1] == turn)
    Number++;

  int i;
  for (i = 2; i <= L; i++) {
    if (n[i] == turn)
      Number++;
    else if (n[i] == 0) {
      if (Number == 0)
        Empty = 1;
      else {
        Scoretmp += ScoreTable(Number, Empty + 1);
        Empty = 1;
        Number = 0;
      }
    } else {
      Scoretmp += ScoreTable(Number, Empty);
      Empty = 0;
      Number = 0;
    }
  }
  Scoretmp += ScoreTable(Number, Empty);
  return Scoretmp;
}

int Evaluate() //评估函数，评估局势
{
  int ScoreME = 0, ScoreOTHER = 0;
  //横排
  int n[505] = {0}, i, j;
  for (i = 0; i < BOARD_SIZE; i++) {
    // vector<int> n;
    for (j = 0; j < BOARD_SIZE; j++)
      n[++n[0]] = Map[i][j];
    ScoreME += CountScore(n, ai_player);
    ScoreOTHER += CountScore(n, OTHER(ai_player));
    n[0] = 0;
  }

  //竖排
  for (j = 0; j < BOARD_SIZE; j++) {
    for (i = 0; i < BOARD_SIZE; i++)
      n[++n[0]] = Map[i][j];
    ScoreME += CountScore(n, ai_player);
    ScoreOTHER += CountScore(n, OTHER(ai_player));
    n[0] = 0;
  }

  //上半正斜线
  for (i = 0; i < BOARD_SIZE; i++) {
    int x, y;
    for (x = i, y = 0; x < BOARD_SIZE && y < BOARD_SIZE; x++, y++)
      n[++n[0]] = Map[y][x];
    ScoreME += CountScore(n, ai_player);
    ScoreOTHER += CountScore(n, OTHER(ai_player));
    n[0] = 0;
  }

  //下半正斜线
  for (j = 1; j < BOARD_SIZE; j++) {
    int x, y;
    for (x = 0, y = j; y < BOARD_SIZE && x < BOARD_SIZE; x++, y++)
      n[++n[0]] = Map[y][x];
    ScoreME += CountScore(n, ai_player);
    ScoreOTHER += CountScore(n, OTHER(ai_player));
    n[0] = 0;
  }

  //上半反斜线
  for (i = 0; i < BOARD_SIZE; i++) {
    int x, y;
    for (y = i, x = 0; y >= 0 && x < BOARD_SIZE; y--, x++)
      n[++n[0]] = Map[y][x];
    ScoreME += CountScore(n, ai_player);
    ScoreOTHER += CountScore(n, OTHER(ai_player));
    n[0] = 0;
  }

  //下半反斜线
  for (j = 1; j < BOARD_SIZE; j++) {
    int x, y;
    for (y = j, x = BOARD_SIZE - 1; y < BOARD_SIZE && x >= 0; y++, x--)
      n[++n[0]] = Map[x][y];
    ScoreME += CountScore(n, ai_player);
    ScoreOTHER += CountScore(n, OTHER(ai_player));
    n[0] = 0;
  }
  return ScoreME - ScoreOTHER;
}

int Min_AlphaBeta(int Dep, int alpha,
                  int beta) // 当 min（对手）走步时，对手的最好情况
{
  int res = Evaluate();
  if (Dep == 0)
    return res;

  struct Position v[505];
  // EmptyPoint(v);
  v[0].x = 0;
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      if (Map[i][j] == NO_CHESS && Around(i, j)) {
        v[++v[0].x].x = i;
        v[v[0].x].y = j;
      }

  int L = v[0].x;
  int best = INT_MAX;
  for (i = 1; i <= L; i++) {
    Map[v[i].x][v[i].y] = OTHER(ai_player);
    // 我是极小层，我要的是更小的数。我找过的孩子中，目前为止找到的最小的数是best，如果best小于了
    // 前辈们之前找到的最小值，那么我将更新它，并且告诉下面未遍历过的孩子，比alpha大的数就不要再给我了
    int tmp = Max_AlphaBeta(Dep - 1, best < alpha ? best : alpha, beta);
    Map[v[i].x][v[i].y] = NO_CHESS;
    if (tmp < best)
      best = tmp;
    if (tmp < beta)
      break;
  }
  return best;
}

int Max_AlphaBeta(int Dep, int alpha, int beta) // AI走步时应该考虑最好的情况
{
  int res = Evaluate();
  if (Dep == 0)
    return res;

  struct Position v[505];
  // EmptyPoint(v);
  int i, j;
  v[0].x = 0;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      if (Map[i][j] == NO_CHESS && Around(i, j)) {
        v[++v[0].x].x = i;
        v[v[0].x].y = j;
      }

  int L = v[0].x;
  int best = INT_MIN;
  for (i = 1; i <= L; i++) {
    Map[v[i].x][v[i].y] = ai_player;
    int tmp = Min_AlphaBeta(Dep - 1, alpha, best > beta ? best : beta);
    Map[v[i].x][v[i].y] = NO_CHESS;
    if (tmp > best)
      best = tmp;
    // 这是极大层，电脑选取最大值点。到目前为止(i=0)，已知tmp。那么该层向上返回的值将不小于tmp
    if (tmp > alpha)
      break;

    // 我的上一层告诉我，它找到的最小的数是alpha，它是极小层，他需要更小的数。
    // 如果我找到的tmp比alpha大，那么就不要找了，因为我是极大层，我只会返回更大的数给上一层
  }
  return best;
}

struct Position MinMax_AlphaBeta(int Dep) //极大极小值算法搜索n步后的最优解
{
  struct Position v[505], v2[505];
  // EmptyPoint(v);
  v[0].x = 0;
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      if (Map[i][j] == NO_CHESS && Around(i, j)) {
        v[++v[0].x].x = i;
        v[v[0].x].y = j;
      }

  int best = INT_MIN;
  int L = v[0].x;
  v2[0].x = 0; // v2[0].x 表示 v2 中的元素数量

  for (i = 1; i <= L; i++) {
    Map[v[i].x][v[i].y] = ai_player; //选该子，将该子置白，防止后面递归时，再递归到
    int tmp = Min_AlphaBeta(Dep, INT_MAX, INT_MIN);
    if (tmp == best)
      v2[++v2[0].x] = v[i];
    if (tmp > best) {
      best = tmp;
      v2[0].x = 0;
      v2[++v2[0].x] = v[i];
    }
    Map[v[i].x][v[i].y] =
        NO_CHESS; //假设完之后，该子需要重新置空，恢复原来的样子
  }

  L = v2[0].x;
  
  srand(time(NULL));
  int k = (int)(rand() % L) + 1;
  return v2[k];
}

struct Position aiBegin(const int board[BOARD_SIZE][BOARD_SIZE], int me) {
  struct Position preferedPos;

  preferedPos.x = (BOARD_SIZE - 1) / 2;
  preferedPos.y = (BOARD_SIZE - 1) / 2;
  return preferedPos;
}

struct Position aiTurn(const int board[BOARD_SIZE][BOARD_SIZE], int me,
                       int otherX, int otherY) {
  int i, j;
  for (i = 0; i < BOARD_SIZE; i++)
    for (j = 0; j < BOARD_SIZE; j++)
      Map[i][j] = board[i][j];

  struct Position preferedPos = MinMax_AlphaBeta(2);
  return preferedPos;
}

void set_ai_player(int player) { ai_player = player; }

int get_ai_player() { return ai_player; }

int ai_begin() {
    struct Position pos = aiBegin(NULL, 0);
    return (pos.x << 16) | pos.y;
}

int ai_turn(const int (*board)[12]) {
    struct Position pos = aiTurn(board, 0, 0, 0);
    return (pos.x << 16) | pos.y;
}