#include "game.h"
#include <QVector>
#include <QHash>
#include <QDebug>
#include <QRandomGenerator>
#include <QTime>

Game::Game() {}
Game::~Game() {}
inline bool Game::IsValid(int x, int y) { return x >= 0 && x < this->row && y >= 0 && y < this->column; }

inline bool Game::IsMine(int x, int y) { return this->mine[x][y]; }

inline bool Game::IsFlag(int x, int y) { return this->map[x][y] == TYPE::FLAG; }

int Game::CountAdjacency(int x, int y, bool (Game::*Func)(int, int)) {
    int cnt = 0;
    for (auto i : {x - 1, x, x + 1}) {
        for (auto j : {y - 1, y, y + 1}) {
            if (i == x && j == y) { continue; }
            if (!IsValid(i, j)) { continue; }
            if ((this->*Func)(i, j)) { ++cnt; }
        }
    }
    return cnt;
}

void Game::VisAdjacency(int x, int y, void (Game::*Func)(int, int)) {
    for (auto i : {x - 1, x, x + 1}) {
        for (auto j : {y - 1, y, y + 1}) {
            if (i == x && j == y) { continue; }
            if (!IsValid(i, j)) { continue; }
            (this->*Func)(i, j);
        }
    }
}

void Game::Start(LEVEL _level, int customRow, int customColumn, int customMineNum) {
    this->level = _level;
    this->SetState(STATE::INGAME);
    this->firstStep = true;
    this->step = 0;
    if (level == LEVEL::EASY) {
        this->column = 9;
        this->row = 9;
        this->mineNum = 10;
    } else if (level == LEVEL::MEDIUM) {
        this->column = 16;
        this->row = 16;
        this->mineNum = 40;
    } else if (level == LEVEL::HARD) {
        this->column = 16;
        this->row = 30;
        this->mineNum = 99;
    } else if (level == LEVEL::CUSTOM) {
        this->column = qMax(qMin(customColumn, 75), 2);
        this->row = qMax(qMin(customRow, 75), 2);
        this->mineNum = qMax(qMin(customMineNum, this->row * this->column - 1), 1);
    }
    this->mineRemain = this->mineNum;
    this->map = QVector<QVector<TYPE>>(this->row, QVector<TYPE>(this->column, TYPE::UNCLICKED));
    this->mine = QVector<QVector<bool>>(this->row, QVector<bool>(this->column, false));
}

TYPE Game::GetType(int x, int y) {
    if (!this->IsValid(x, y)) { return TYPE::NULLTYPE; }
    return this->map[x][y];
}

inline bool Game::SetType(int x, int y, TYPE newType) {
    if (!this->IsValid(x, y)) { return false; }
    this->map[x][y] = newType;
    return true;
}

inline bool Game::SetState(STATE newState) {
    this->state = newState;
    return true;
}

const QVector<QVector<TYPE>>& Game::GetMap() {
    return this->map;
}

int Game::GetRow() {
    return this->row;
}

int Game::GetColumn() {
    return this->column;
}


STATE Game::GetState() {
    return this->state;
}

bool Game::Click(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    if (GetNum(x, y) != -1) { return false; }
    if (this->firstStep) {
        this->GenerateMine(x, y);
        this->firstStep = false;
    }
    auto dfs = [&](auto dfs, int curX, int curY) {
        if (this->GetState() == STATE::LOSE) { return; }
        if (!this->IsValid(curX, curY)) { return; }
        if (this->GetType(curX, curY) != TYPE::UNCLICKED) { return; }
        if (IsMine(x, y)) {
            this->SetState(STATE::LOSE);
            return;
        }
        int mineCnt = CountAdjacency(curX, curY, &Game::IsMine);
        this->SetType(curX, curY, TYPE(mineCnt));
        if (mineCnt == 0) {
            for (auto i : {curX - 1, curX, curX + 1}) {
                for (auto j : {curY - 1, curY, curY + 1}) {
                    if (GetType(i, j) == TYPE::UNCLICKED) { dfs(dfs, i, j); }
                }
            }
        }
    };
    dfs(dfs, x, y);
    ++step;
    return true;
}

bool Game::SetFlag(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    // if (this->map[x][y] != TYPE::UNCLICKED) { return false; }
    this->CancelMark(x, y);
    this->SetType(x, y, TYPE::FLAG);
    return true;
}

bool Game::SetUnknown(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    // if (this->GetType(x, y) != TYPE::FLAG) { return false; }
    this->CancelMark(x, y);
    this->SetType(x, y, TYPE::UNKNOWN);
    return true;
}

bool Game::CancelMark(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    if (this->GetType(x, y) == TYPE::FLAG) {
        ++this->mineRemain;
        this->SetType(x, y, TYPE::UNCLICKED);
        return true;
    } else if (this->GetType(x, y) == TYPE::UNKNOWN) {
        this->SetType(x, y, TYPE::UNCLICKED);
        return true;
    } else {
        --this->mineRemain;
    }
    return false;
}

bool Game::RightClick(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    if (this->GetType(x, y) == TYPE::UNCLICKED) { ++step; return this->SetFlag(x, y); }
    else if (this->GetType(x, y) == TYPE::FLAG) { ++step; return this->SetUnknown(x, y); }
    else if (this->GetType(x, y) == TYPE::UNKNOWN) { ++step; return this->CancelMark(x, y); }
    return false;
}

inline int Game::GetNum(int x, int y) {
    if (!this->IsValid(x, y)) { return -1; }
    if (int(this->GetType(x, y)) >= 9) { return -1; }
    return int(this->GetType(x, y));
}

int Game::GetStep() {
    return this->step;
}

bool Game::DoubleClick(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    int num = GetNum(x, y);
    if (num == -1) { return false; }
    int cnt = this->CountAdjacency(x, y, &Game::IsFlag);
    if (cnt != num) { return false; }
    this->CountAdjacency(x, y, &Game::Click);
    ++step;
    return true;
}

void Game::GenerateMine(int x, int y) {
    QRandomGenerator randP(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    for (int i = 0; i < this->mineNum; i++) {
        int newX = 0, newY = 0;
        do {
            newX = randP.generate() % this->row;
            newY = randP.generate() % this->column;
        } while (this->IsMine(newX, newY) || (newX == x && newY == y));
        // std::cout << newX << " " << newY << std::endl;
        this->mine[newX][newY] = true;
    }
}

void Game::Check() {
    for (int i = 0; i < this->GetRow(); i ++) {
        for (int j = 0; j < this->GetColumn(); j ++) {
            if (!IsMine(i, j) && this->GetNum(i, j) == -1) { return; }
        }
    }
    this->SetState(STATE::WIN);
}

void Game::End() {
    for (int i = 0; i < this->GetRow(); i ++) {
        for (int j = 0; j < this->GetColumn(); j ++) {
            if (!this->IsMine(i, j) && this->IsFlag(i, j)) {
                this->SetType(i, j, TYPE::MINE_WRONG);
            } else if (this->IsMine(i, j)) {
                this->SetType(i, j, this->GetState() == STATE::WIN ? TYPE::MINE : TYPE::MINE_EXPLODE);
            }
        }
    }
}

int Game::GetRemainMine()
{ return this->mineRemain; }
