#pragma once
#ifndef CHESSALGORITHM_H
#define CHESSALGORITHM_H

#include <QObject>
#include <QPoint>
#include"ChessBoard.h"

class ChessAlgorithm : public QObject
{
    Q_OBJECT
        Q_PROPERTY(Result result READ result)
        Q_PROPERTY(Player currentPlayer
            READ currentPlayer
            NOTIFY currentPlayerChanged)
public:
    enum Result { NoResult, PlayerWhiteWins, Draw, PlayerDarkWins };
    Q_ENUM(Result)
        enum Player { NoPlayer, PlayerWhite, PlayerDark };
    Q_ENUM(Player)

        explicit ChessAlgorithm(QObject* parent = 0);
    ChessBoard* board() const;
    inline Result result() const {
        return m_result;
    }
    inline Player currentPlayer() const {
        return m_currentPlayer;
    }

signals:
    void boardChanged(ChessBoard*);
    void gameOver(Result);
    void currentPlayerChanged(Player);

public slots:
    virtual void newGame();
    virtual bool move(int colFrom, int rankFrom, int colTo, int rankTo);
    bool move(const QPoint& from, const QPoint& to);

protected:
    virtual void setupBoard();
    void setBoard(ChessBoard* board);
    void setResult(Result);
    void setCurrentPlayer(Player);
private:
    ChessBoard* m_board;
    Result m_result;
    Player m_currentPlayer;
};

#endif // CHESSALGORITHM_H
