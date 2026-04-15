#pragma once
#include"ChessAlgorithm.h"
#include <QMessageBox>

class ChessGame : public ChessAlgorithm
{
public:
    ChessGame(QObject* parent = 0);
    void newGame();
    bool move(int colFrom, int rankFrom, int colTo, int rankTo);
    bool whiteKingCanMove() const;
    bool blackKingCanMove() const;
    QPoint findKing(Player player) const;
    bool isSquareAttackedBy(int col, int rank, Player attacker) const;
    bool isKingInCheck(Player player) const;
    bool moveLeavesKingInCheck(int colFrom, int rankFrom, int colTo, int rankTo, Player player);
    bool kingSurvives(int kingCol, int kingRank, int oppositeKingCol, int oppositeKingRank, int queenCol, int queenRank, int knightCol, int knightRank, int bishopCol, int bishopRank, int rookCol, int rookRank)const;
    bool kingSurvivesPawns(int kingCol,int kingRank,int pawn1Col, int pawn1Rank, int pawn2Col, int pawn2Rank, int pawn3Col, int pawn3Rank, int pawn4Col, int pawn4Rank, int pawn5Col, int pawn5Rank, int pawn6Col, int pawn6Rank, int pawn7Col, int pawn7Rank, int pawn8Col, int pawn8Rank)const;
    bool kingEaten(int rankTo, int colTo, int oppositeKingCol, int oppositeKingRank, int queenCol, int queenRank, int knightCol, int knightRank, int bishopCol, int bishopRank, int rookCol, int rookRank)const;
    bool kingEatenByPawns(int colTo, int rankTo, int pawn1Col, int pawn1Rank, int pawn2Col, int pawn2Rank, int pawn3Col, int pawn3Rank, int pawn4Col, int pawn4Rank, int pawn5Col, int pawn5Rank, int pawn6Col, int pawn6Rank, int pawn7Col, int pawn7Rank, int pawn8Col, int pawn8Rank)const;
    bool pawnEats(int rankDelta, int colDelta)const;
    bool kingEats(int rankDelta, int colDelta) const;
    bool queenEats(int rankDelta, int colDelta, int rankFrom, int colFrom)const;
    bool knightEats(int rankDelta, int colDelta)const;
    bool bishopEats(int rankDelta, int colDelta, int rankFrom, int colFrom) const;
    bool rookEats(int rankDelta, int colDelta, int rankFrom, int colFrom) const;
private:
    QPoint m_whiteKing= QPoint(5, 1);
    QPoint m_blackKing= QPoint(5, 8);
    QPoint m_whiteQueen = QPoint(4, 1);
    QPoint m_blackQueen = QPoint(4, 8);
    QPoint m_whiteBishop1= QPoint(6, 1);
    QPoint m_whiteBishop2 = QPoint(3, 1);
    QPoint m_blackBishop1= QPoint(3, 8);
    QPoint m_blackBishop2 = QPoint(6, 8);
    QPoint m_whiteRook1= QPoint(8, 1);
    QPoint m_whiteRook2 = QPoint(1, 1);
    QPoint m_blackRook1= QPoint(1, 8);
    QPoint m_blackRook2 = QPoint(8, 8);
    QPoint m_whiteKnight1 = QPoint(7, 1);
    QPoint m_whiteKnight2 = QPoint(2, 1);
    QPoint m_blackKnight1 = QPoint(2, 8);
    QPoint m_blackKnight2 = QPoint(7, 8);
    QPoint m_whitePawn1 = QPoint(1, 2);
    QPoint m_whitePawn2 = QPoint(2, 2);
    QPoint m_whitePawn3 = QPoint(3, 2);
    QPoint m_whitePawn4 = QPoint(4, 2);
    QPoint m_whitePawn5 = QPoint(5, 2);
    QPoint m_whitePawn6 = QPoint(6, 2);
    QPoint m_whitePawn7 = QPoint(7, 2);
    QPoint m_whitePawn8 = QPoint(8, 2);
    QPoint m_blackPawn1 = QPoint(1, 2);
    QPoint m_blackPawn2 = QPoint(2, 2);
    QPoint m_blackPawn3 = QPoint(3, 2);
    QPoint m_blackPawn4 = QPoint(4, 2);
    QPoint m_blackPawn5 = QPoint(5, 2);
    QPoint m_blackPawn6 = QPoint(6, 2);
    QPoint m_blackPawn7 = QPoint(7, 2);
    QPoint m_blackPawn8 = QPoint(8, 2);
    

};
