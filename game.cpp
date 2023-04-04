#include "game.h"
#include <QVector>
#include <QHash>
#include <QDebug>
#include <QRandomGenerator>
#include <QTime>
#include <iostream>

Game::Game(LEVEL _level, size_t customRow, size_t customColumn, int customMineNum): level(_level) {
    if (level == LEVEL::EASY) {
        this->column = 9;
        this->row = 9;
        this->mineNum = 10;
    } else if (level == LEVEL::MIDIUM) {
        this->column = 16;
        this->row = 16;
        this->mineNum = 40;
    } else if (level == LEVEL::HARD) {
        this->column = 30;
        this->row = 16;
        this->mineNum = 99;
    } else if (level == LEVEL::CUSTOM) {
        this->column = customColumn;
        this->row = customRow;
        this->mineNum = qMin(customMineNum, int(this->row * this->column - 1));
    }
    this->map.resize(this->row, QVector<TYPE>(this->column, TYPE::UNCLICKED));
    this->mine.resize(this->row, QVector<bool>(this->column, false));
}

inline bool Game::IsValid(int x, int y) { return x >= 0 && x <= this->row && y >= 0 && this->column; }

inline bool Game::IsMine(int x, int y) { return mine[x][y]; }

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

void Game::Start() {
    this->SetState(STATE::INGAME);
    GenerateMine();
}

inline TYPE Game::GetType(int x, int y) {
    if (!IsValid(x, y)) { return TYPE::NULLTYPE; }
    return this->map[x][y];
}

inline bool Game::SetType(int x, int y, TYPE newType) {
    if (!IsValid(x, y)) { return false; }
    this->map[x][y] = newType;
    return true;
}

inline bool Game::SetState(STATE newState) {
    this->state = newState;
    return true;
}

inline const QVector<QVector<TYPE>>& Game::GetMap() {
    return this->map;
}


inline Game::STATE Game::GetState() {
    return this->state;
}

bool Game::Click(int x, int y) {
    if (!IsValid(x, y)) { return false; }

    auto dfs = [&](auto dfs, int curX, int curY) {
        if (this->state == STATE::LOSE) { return; }
        if (!this->IsValid(curX, curY)) { return; }
        if (this->map[curX][curY] != TYPE::UNCLICKED) { return; }
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
        --this->mineRemain;
        this->SetType(x, y, TYPE::UNCLICKED);
        return true;
    }
    return false;
}

bool Game::RightClick(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    if (this->GetType(x, y) == TYPE::UNCLICKED) { return this->SetFlag(x, y); }
    else if (this->GetType(x, y) == TYPE::FLAG) { return this->SetUnknown(x, y); }
    else if (this->GetType(x, y) == TYPE::UNKNOWN) { return this->CancelMark(x, y); }
    return false;
}

inline int Game::GetNum(int x, int y) {
    if (!this->IsValid(x, y)) { return -1; }
    if (int(this->GetType(x, y)) >= 9) { return -1; }
    return int(this->GetType(x, y));
}

bool Game::DoubleClick(int x, int y) {
    if (!this->IsValid(x, y)) { return false; }
    int num = GetNum(x, y);
    if (num == -1) { return false; }
    int cnt = this->CountAdjacency(x, y, &Game::IsMine);
    if (cnt != num) { return false; }
    this->CountAdjacency(x, y, &Game::Click);
    return true;
}

QHash<TYPE, char> to {
    {TYPE::UNCLICKED, '.'},
    {TYPE::FLAG, '!'},
    {TYPE::ZERO, '0'},
    {TYPE::ONE, '1'},
    {TYPE::TWO, '2'},
    {TYPE::THREE, '3'},
    {TYPE::FOUR, '4'},
    {TYPE::FIVE, '5'},
    {TYPE::SIX, '6'},
    {TYPE::SEVEN, '7'},
    {TYPE::EIGHT, '8'},
    {TYPE::UNKNOWN, '?'},
    {TYPE::MINE, '*'},
};

void Game::GenerateMine() {
    QRandomGenerator randP(QTime(0,0,0).secsTo(QTime::currentTime()));
    for (int i = 0; i < this->mineNum; i++) {
        int newX = 0;
        int newY = 0;
        do {
            newX = randP.generate() % this->row;
            newY = randP.generate() % this->column;
        } while (this->GetType(newX, newY) == TYPE::MINE);
        // std::cout << newX << " " << newY << std::endl;
        this->mine[newX][newY] = true;
        // this->SetType(newX, newY, TYPE::MINE);
    }
}

void Game::Print() {
    for (int i = 0; i < this->row; i ++) {
        for (int j = 0; j < this->column; j ++) {
            std::cout << to[this->GetType(i, j)];
        }
        std::cout << "\n";
    }

    std::cout << "end\n";
}
