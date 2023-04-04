#ifndef GAME_H
#define GAME_H
#include <QApplication>


enum class TYPE { ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, MINE, FLAG, UNKNOWN, UNCLICKED, NULLTYPE };
enum class LEVEL { EASY, MIDIUM, HARD, CUSTOM };

class Game
{
private:

    enum class STATE { INGAME, WIN, LOSE };

    LEVEL level;
    STATE state;

    QVector<QVector<TYPE>> map;
    QVector<QVector<bool>> mine;
    size_t column, row;
    int mineNum, mineRemain;

    inline bool IsValid(int x, int y);

    void GenerateMine();
    int CountAdjacency(int x, int y, bool (Game::*Func)(int, int));
    void VisAdjacency(int x, int y, void (Game::*Func)(int, int));
    bool SetFlag(int x, int y);
    bool SetUnknown(int x, int y);
    bool CancelMark(int x, int y);
    bool IsMine(int x, int y);

public:
    Game(LEVEL _level = LEVEL::EASY, size_t customRow = 9, size_t customColumn = 9, int customMineNum = 10);
    ~Game() {};

    inline bool SetState(STATE newState);
    inline bool SetType(int x, int y, TYPE newType);
    inline int GetNum(int x, int y);
    inline const QVector<QVector<TYPE>>& GetMap();
    inline STATE GetState();
    inline TYPE GetType(int x, int y);

    void Start();
    bool Click(int x, int y);
    bool RightClick(int x, int y);
    bool DoubleClick(int x, int y);

    void Print();
};

#endif // GAME_H
