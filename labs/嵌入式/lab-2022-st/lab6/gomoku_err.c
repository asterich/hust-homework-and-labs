#include "gomoku_err.h"
#include "gomoku.h"

char *get_err_msg(int err_code) {
    switch (err_code) {
    case OK:
        return "OK";
    case ERR_GAME_OVER:
        return "哥哥，游戏已经结束啦！";
    case ERR_GAME_NOT_STARTED:
        return "哥哥，游戏还没开始哦";
    case ERR_GAME_NOT_OVER:
        return "哥哥，游戏还没结束，不能重开哦";
    case ERR_NOT_YOUR_TURN:
        return "坏蛋哥哥，还没轮到你下呢";
    case ERR_INVALID_POS:
        return "哥哥，你下的位置不对哦";
    case ERR_OCCUPIED:
        return "坏蛋哥哥，这里已经有棋子啦！";
    default:
        return "unknown error";
    }
}