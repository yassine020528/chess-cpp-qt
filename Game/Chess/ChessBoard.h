#pragma once
#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QObject>
#include <QVector>

class ChessBoard : public QObject
{
    Q_OBJECT
        Q_PROPERTY(int ranks READ ranks NOTIFY ranksChanged)
        Q_PROPERTY(int columns READ columns NOTIFY columnsChanged)

public:
    explicit ChessBoard(int ranks = 8, int columns = 8, QObject* parent = nullptr);
    int ranks() const;
    int columns() const;
    char data(int column, int rank) const;
    void setData(int column, int rank, char value);
    void movePiece(int fromColumn, int fromRank,
        int toColumn, int toRank);
    void setFen(const QString& fen);

signals:
    void ranksChanged(int newRanks);
    void columnsChanged(int newColumns);
    void dataChanged(int column, int rank);
    void boardReset();

protected:
    void initBoard();
    void setRanks(int newRanks);
    void setColumns(int newColumns);
    bool setDataInternal(int column, int rank, char value);

private:
    QVector<char> m_boardData;
    int m_ranks;
    int m_columns;
};

#endif // CHESSBOARD_H
