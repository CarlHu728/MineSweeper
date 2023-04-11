#ifndef GAME_H
#define GAME_H
#include <QApplication>
#include <QTImer>

enum class TYPE { ZERO = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, MINE, UNCLICKED, FLAG, MINE_WRONG, MINE_EXPLODE, UNKNOWN, NULLTYPE };
enum class LEVEL { EASY, MEDIUM, HARD, CUSTOM };
enum class STATE { INGAME, WIN, LOSE };

class Game : public QObject
{
private:
    LEVEL level;
    STATE state;

    QVector<QVector<TYPE>> map;
    QVector<QVector<bool>> mine;
    int column, row;
    int mineNum, mineRemain;
    int step;
    bool firstStep;
    bool isOnline;
    bool isHost;
    int roomCode;

    inline bool IsValid(int x, int y);
    inline bool IsFlag(int x, int y);

    void GenerateMine(int x, int y);
    int CountAdjacency(int x, int y, bool (Game::*Func)(int, int));
    void VisAdjacency(int x, int y, void (Game::*Func)(int, int));
    bool SetFlag(int x, int y);
    bool SetUnknown(int x, int y);
    bool CancelMark(int x, int y);
    bool IsMine(int x, int y);


public:
    Game();
    ~Game();

    inline bool SetState(STATE newState);
    inline bool SetType(int x, int y, TYPE newType);
    inline int GetNum(int x, int y);
    const QVector<QVector<TYPE>>& GetMap();
    STATE GetState();
    TYPE GetType(int x, int y);
    int GetStep();
    int GetRemainMine();
    int GetRow();
    int GetColumn();

    void Start(LEVEL level, int customRow = 9,
               int customColumn = 9, int customMineNum = 10);
    void SetOnlineState(bool isOnline, bool isHost = -1, int roomCode = -1);
    bool Click(int x, int y);
    bool RightClick(int x, int y);
    bool DoubleClick(int x, int y);
    int newRoom();
    bool joinRoom(int roomCode);
    bool exitRoom();
    void Check();
    void End();
};

#endif // GAME_H
