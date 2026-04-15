#include"ChessLivrable.h"

ChessLivrable::ChessLivrable(QObject* parent)
    : ChessAlgorithm(parent)
{
}
void ChessLivrable ::newGame()
{
    setupBoard();
    board()->setFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w");
    // 'w' - white to move
    
    setResult(NoResult);
    setCurrentPlayer(PlayerWhite);
}
bool ChessLivrable::move(int colFrom, int rankFrom,
    int colTo, int rankTo)
{
    if (currentPlayer() == NoPlayer) {
        QMessageBox::warning(nullptr, "Erreur", "Game is over");
        return false;
    }

    // is there a piece of the right color?
    char source = board()->data(colFrom, rankFrom);
    if (currentPlayer() == PlayerWhite && source != 'K' && source != 'R' && source != 'B' && source != 'N' && source!='Q' && source != 'P') {
        QMessageBox::warning(nullptr, "Erreur", "Tour a l'autre joueur");
        return false;
    };
    if (currentPlayer() == PlayerDark && source != 'k' && source != 'r' && source != 'b' && source != 'n' && source != 'q' && source != 'p') {
        QMessageBox::warning(nullptr, "Erreur", "Tour a l'autre joueur");
        return false;
    };

    // do we move within the board?
    if (colTo < 1 || colTo  > board()->columns()) {
        QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
        return false;
    };

    if (rankTo < 1 || rankTo > board()->ranks()) {
        QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
        return false;
    };

    char destination = board()->data(colTo, rankTo);
    // is move for a white pawn valid
    if (currentPlayer() == PlayerWhite && source == 'P') {
        if (destination == ' ') {
            if(rankFrom==2){
                if ((colFrom != colTo) || ((rankTo != rankFrom + 1)&& (rankTo != rankFrom + 2))) {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            }
            else if ((colFrom != colTo) || rankTo != rankFrom + 1) {
                QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                return false;
            };
        };
        if (destination == 'k' || destination == 'r' || destination == 'b' || destination == 'n' || destination == 'q' || destination == 'p') {
            if (((colFrom != colTo - 1) && (colFrom != colTo + 1)) || (rankTo != rankFrom + 1)) {
                QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                return false;
            };
        };
    };
    // is move for a black pawn valid
    if (currentPlayer() == PlayerDark && source == 'p') {
        if (destination == ' ') {
            if (rankFrom == 7) {
                if ((colFrom != colTo) || ((rankTo != rankFrom - 1) && (rankTo != rankFrom - 2))) {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            }
            else if ((colFrom != colTo) || rankTo != rankFrom - 1) {
                QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                return false;
            };
        };
        if (destination == 'K' || destination == 'R' || destination == 'B' || destination == 'N' || destination == 'Q' || destination == 'P') {
            if (((colFrom != colTo - 1) && (colFrom != colTo + 1)) || (rankTo != rankFrom - 1)) {
                QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                return false;
            };
        };
    };
    // is the move for a king valid
    if ((currentPlayer() == PlayerWhite && source == 'K') || (currentPlayer() == PlayerDark && source == 'k')) {
        if (((rankTo != rankFrom || colTo != colFrom) && (rankTo != rankFrom || colTo != colFrom + 1) && (rankTo != rankFrom || colTo != colFrom + -1))
            && ((rankTo != rankFrom - 1 || colTo != colFrom) && (rankTo != rankFrom - 1 || colTo != colFrom + 1) && (rankTo != rankFrom - 1 || colTo != colFrom + -1))
            && ((rankTo != rankFrom + 1 || colTo != colFrom) && (rankTo != rankFrom + 1 || colTo != colFrom + 1) && (rankTo != rankFrom + 1 || colTo != colFrom + -1))) {
            QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
            return false;
        };
    };

    // is the move for a queen valid
    if ((currentPlayer() == PlayerWhite && source == 'Q') || (currentPlayer() == PlayerDark && source == 'q')) {
        int rankDelta = rankTo - rankFrom;
        int colDelta = colTo - colFrom;

        // Check if the move is valid for a queen
        if (rankDelta == colDelta && rankDelta > 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom + counter, rankFrom + counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };

        }
        else if (rankDelta == colDelta && rankDelta < 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom - counter, rankFrom - counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta == -colDelta && rankDelta > 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom - counter, rankFrom + counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta == -colDelta && rankDelta < 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom + counter, rankFrom - counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta == 0 && colDelta != 0 && colDelta > 0) {
            for (int counter = 1; counter < abs(colDelta); counter++) {
                char destination = board()->data(colFrom + counter, rankFrom);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta == 0 && colDelta != 0 && colDelta < 0) {
            for (int counter = 1; counter < abs(colDelta); counter++) {
                char destination = board()->data(colFrom - counter, rankFrom);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta != 0 && colDelta == 0 && rankDelta > 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom, rankFrom + counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta != 0 && colDelta == 0 && rankDelta < 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom, rankFrom - counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else {
            QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
            return false; // move is not vertical or horizontal or diagonal
        };
    };

    // is the move for a knight valid
    if ((currentPlayer() == PlayerWhite && source == 'N') || (currentPlayer() == PlayerDark && source == 'n')) {
        int rowDelta = rankTo - rankFrom;
        int colDelta = colTo - colFrom;
        // Check if the move is valid for a knight
        if ((abs(rowDelta) != 2 || abs(colDelta) != 1) && (abs(rowDelta) != 1 || abs(colDelta) != 2)) {
            QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
            return false; // move is not valid
        };
    };

    // is the move for a bishop valid
    if ((currentPlayer() == PlayerWhite && source == 'B') || (currentPlayer() == PlayerDark && source == 'b')) {
        int rankDelta = rankTo - rankFrom;
        int colDelta = colTo - colFrom;
        
        // Check if the move is valid for a bishop
        if (rankDelta == colDelta && rankDelta > 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom + counter, rankFrom + counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };

        }
        else if (rankDelta == colDelta && rankDelta < 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom - counter, rankFrom - counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta == -colDelta && rankDelta > 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom - counter, rankFrom + counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta == -colDelta && rankDelta < 0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom + counter, rankFrom - counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else {
            QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
            return false; // move is not diagonal
        };
    };

    // is the move for a rook valid
    if ((currentPlayer() == PlayerWhite && source == 'R') || (currentPlayer() == PlayerDark && source == 'r')) {
        int rankDelta = rankTo - rankFrom;
        int colDelta = colTo - colFrom;

        // Check if the move is valid for a rook
        
        if (rankDelta == 0 && colDelta != 0 && colDelta>0) {
            for (int counter = 1; counter < abs(colDelta); counter++) {
                char destination = board()->data(colFrom + counter, rankFrom);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta == 0 && colDelta != 0 && colDelta <0) {
            for (int counter = 1; counter < abs(colDelta); counter++) {
                char destination = board()->data(colFrom - counter, rankFrom);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta != 0 && colDelta == 0 && rankDelta>0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom, rankFrom+counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else if (rankDelta != 0 && colDelta == 0 && rankDelta <0) {
            for (int counter = 1; counter < abs(rankDelta); counter++) {
                char destination = board()->data(colFrom, rankFrom - counter);
                if (destination != ' ') {
                    QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
                    return false;
                };
            };
        }
        else {
            QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
            return false; // move is not vertical or horizontal
        };
    };
    
    // is the destination field empty or has an opposite color piece?
    destination = board()->data(colTo, rankTo);
    if (currentPlayer() == PlayerWhite) {
        if (destination != ' ' && destination != 'k' && destination != 'b' && destination != 'r' && destination != 'n' && destination != 'q' && destination != 'p') {
            QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
            return false;
        };
    };
    if (currentPlayer() == PlayerDark) {
        if (destination != ' ' && destination != 'K' && destination != 'B' && destination != 'R' && destination != 'N' && destination != 'Q' && destination != 'P') {
            QMessageBox::warning(nullptr, "Erreur", "Mouvement invalide");
            return false;
        };
    };

    // make the move
    board()->movePiece(colFrom, rankFrom, colTo, rankTo);

    if (currentPlayer() == PlayerWhite && source == 'K') {
        m_whiteKing = QPoint(colTo, rankTo); // cache white king position
    }
    if (currentPlayer() == PlayerDark && source == 'k') {
        m_blackKing = QPoint(colTo, rankTo); // cache black king position
    }

    if (currentPlayer() == PlayerWhite && source == 'Q') {
        m_whiteQueen = QPoint(colTo, rankTo); // cache white queen position
    }
    if (currentPlayer() == PlayerDark && source == 'q') {
        m_blackQueen = QPoint(colTo, rankTo); // cache black queen position
    }

    if (currentPlayer() == PlayerWhite && source == 'N') {
        if (colFrom == m_whiteKnight1.x() && rankFrom == m_whiteKnight1.y()) {
            m_whiteKnight1 = QPoint(colTo, rankTo); // cache white knight position
        }
        else {
            m_whiteKnight2 = QPoint(colTo, rankTo); // cache white knight position
        };
    };
    if (currentPlayer() == PlayerDark && source == 'n') {
        if (colFrom == m_blackKnight1.x() && rankFrom == m_blackKnight1.y()) {
            m_blackKnight1 = QPoint(colTo, rankTo); // cache black knight position
        }
        else {
            m_blackKnight2 = QPoint(colTo, rankTo); // cache black knight position
        };
    };

    if (currentPlayer() == PlayerWhite && source == 'B') {
        if (colFrom == m_whiteBishop1.x() && rankFrom == m_whiteBishop1.y()) {
            m_whiteBishop1 = QPoint(colTo, rankTo); // cache white bishop position
        }
        else {
            m_whiteBishop2 = QPoint(colTo, rankTo); // cache white bishop position
        };
    };
    if (currentPlayer() == PlayerDark && source == 'b') {
        if (colFrom == m_blackBishop1.x() && rankFrom == m_blackBishop1.y()) {
            m_blackBishop1 = QPoint(colTo, rankTo); // cache black bishop position
        }
        else {
            m_blackBishop2 = QPoint(colTo, rankTo); // cache black bishop position
        };
    };

    if (currentPlayer() == PlayerWhite && source == 'R') {
        if (colFrom == m_whiteRook1.x() && rankFrom == m_whiteRook1.y()) {
            m_whiteRook1 = QPoint(colTo, rankTo); // cache white rook position
        }
        else {
            m_whiteRook2 = QPoint(colTo, rankTo); // cache white rook position
        };
    };
    if (currentPlayer() == PlayerDark && source == 'r') {
        if (colFrom == m_blackRook1.x() && rankFrom == m_blackRook1.y()) {
            m_blackRook1 = QPoint(colTo, rankTo); // cache black rook position
        }
        else {
            m_blackRook2 = QPoint(colTo, rankTo); // cache black rook position
        };
    }

    if (currentPlayer() == PlayerWhite && source == 'P') {
        if (colFrom == m_whitePawn1.x() && rankFrom == m_whitePawn1.y()) {
            m_whitePawn1 = QPoint(colTo, rankTo); // cache white pawn position
        }
        else if (colFrom == m_whitePawn2.x() && rankFrom == m_whitePawn2.y()) {
            m_whitePawn2 = QPoint(colTo, rankTo); // cache white pawn position
        }
        else if (colFrom == m_whitePawn3.x() && rankFrom == m_whitePawn3.y()) {
            m_whitePawn3 = QPoint(colTo, rankTo); // cache white pawn position
        }
        else if (colFrom == m_whitePawn4.x() && rankFrom == m_whitePawn4.y()) {
            m_whitePawn4 = QPoint(colTo, rankTo); // cache white pawn position
        }
        else if (colFrom == m_whitePawn5.x() && rankFrom == m_whitePawn5.y()) {
            m_whitePawn5 = QPoint(colTo, rankTo); // cache white pawn position
        }
        else if (colFrom == m_whitePawn6.x() && rankFrom == m_whitePawn6.y()) {
            m_whitePawn6 = QPoint(colTo, rankTo); // cache white pawn position
        }
        else if (colFrom == m_whitePawn7.x() && rankFrom == m_whitePawn7.y()) {
            m_whitePawn7 = QPoint(colTo, rankTo); // cache white pawn position
        }
        else {
            m_whitePawn8 = QPoint(colTo, rankTo); // cache white pawn position
        };
    };
    if (currentPlayer() == PlayerDark && source == 'p') {
        if (colFrom == m_blackPawn1.x() && rankFrom == m_blackPawn1.y()) {
            m_blackPawn1 = QPoint(colTo, rankTo); // cache dark pawn position
        }
        else if (colFrom == m_blackPawn2.x() && rankFrom == m_blackPawn2.y()) {
            m_blackPawn2 = QPoint(colTo, rankTo); // cache dark pawn position
        }
        else if (colFrom == m_blackPawn3.x() && rankFrom == m_blackPawn3.y()) {
            m_blackPawn3 = QPoint(colTo, rankTo); // cache dark pawn position
        }
        else if (colFrom == m_blackPawn4.x() && rankFrom == m_blackPawn4.y()) {
            m_blackPawn4 = QPoint(colTo, rankTo); // cache dark pawn position
        }
        else if (colFrom == m_blackPawn5.x() && rankFrom == m_blackPawn5.y()) {
            m_blackPawn5 = QPoint(colTo, rankTo); // cache dark pawn position
        }
        else if (colFrom == m_blackPawn6.x() && rankFrom == m_blackPawn6.y()) {
            m_blackPawn6 = QPoint(colTo, rankTo); // cache dark pawn position
        }
        else if (colFrom == m_blackPawn7.x() && rankFrom == m_blackPawn7.y()) {
            m_blackPawn7 = QPoint(colTo, rankTo); // cache dark pawn position
        }
        else {
            m_blackPawn8 = QPoint(colTo, rankTo); // cache dark pawn position
        };
    };

    // check win condition
    if ((currentPlayer() == PlayerWhite && !whiteKingCanMove()) || (currentPlayer() == PlayerDark && destination=='K')) {
        setCurrentPlayer(NoPlayer);
        QMessageBox::warning(nullptr, "Game Over", "Dark wins");
        setResult(PlayerDarkWins); // dark wins
        return true;
    };
    if ((currentPlayer() == PlayerDark && !blackKingCanMove()) || (currentPlayer() == PlayerWhite && destination=='k')) {
        setCurrentPlayer(NoPlayer);
        QMessageBox::warning(nullptr, "Game Over", "White wins");
        setResult(PlayerWhiteWins); // white wins
        return true;
    };
    // check if kings at check
    if (currentPlayer() == PlayerDark && !whiteKingCanMove()) {
        QMessageBox::warning(nullptr, "Watch out", "White king at check");
    };
    if (currentPlayer() == PlayerWhite && !blackKingCanMove()) {
        setCurrentPlayer(NoPlayer);
        QMessageBox::warning(nullptr, "Watch out", "Dark king at check");
    };
    // the other player makes the move now
    setCurrentPlayer(currentPlayer() == PlayerWhite ? PlayerDark : PlayerWhite);
    return true;
}
bool ChessLivrable::whiteKingCanMove() const {
    int kingCol = m_whiteKing.x();
    int kingRank = m_whiteKing.y();
    int blackKingCol = m_blackKing.x();
    int blackKingRank = m_blackKing.y();
    int queenCol = m_blackQueen.x();
    int queenRank = m_blackQueen.y();
    int knight1Col = m_blackKnight1.x();
    int knight1Rank = m_blackKnight1.y();
    int bishop1Col = m_blackBishop1.x();
    int bishop1Rank = m_blackBishop1.y();
    int rook1Col = m_blackRook1.x();
    int rook1Rank = m_blackRook1.y();
    int knight2Col = m_blackKnight2.x();
    int knight2Rank = m_blackKnight2.y();
    int bishop2Col = m_blackBishop2.x();
    int bishop2Rank = m_blackBishop2.y();
    int rook2Col = m_blackRook2.x();
    int rook2Rank = m_blackRook2.y();
    int pawn1Col = m_blackPawn1.x();
    int pawn1Rank = m_blackPawn1.y();
    int pawn2Col = m_blackPawn2.x();
    int pawn2Rank = m_blackPawn2.y();
    int pawn3Col = m_blackPawn3.x();
    int pawn3Rank = m_blackPawn3.y();
    int pawn4Col = m_blackPawn4.x();
    int pawn4Rank = m_blackPawn4.y();
    int pawn5Col = m_blackPawn5.x();
    int pawn5Rank = m_blackPawn5.y();
    int pawn6Col = m_blackPawn6.x();
    int pawn6Rank = m_blackPawn6.y();
    int pawn7Col = m_blackPawn7.x();
    int pawn7Rank = m_blackPawn7.y();
    int pawn8Col = m_blackPawn8.x();
    int pawn8Rank = m_blackPawn8.y();
    return kingSurvives(kingCol, kingRank, blackKingCol, blackKingRank, queenCol, queenRank, knight1Col, knight1Rank, bishop1Col, bishop1Rank, rook1Col, rook1Rank)
        || kingSurvives(kingCol, kingRank, blackKingCol, blackKingRank, queenCol, queenRank, knight2Col, knight2Rank, bishop2Col, bishop2Rank, rook2Col, rook2Rank)
        || kingSurvivesPawns(kingCol, kingRank,pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col,pawn8Rank);
}

bool ChessLivrable::blackKingCanMove() const {
    int kingCol = m_blackKing.x();
    int kingRank = m_blackKing.y();
    int whiteKingCol = m_whiteKing.x();
    int whiteKingRank = m_whiteKing.y();
    int queenCol = m_whiteQueen.x();
    int queenRank = m_whiteQueen.y();
    int knight1Col = m_whiteKnight1.x();
    int knight1Rank = m_whiteKnight1.y();
    int bishop1Col = m_whiteBishop1.x();
    int bishop1Rank = m_whiteBishop1.y();
    int rook1Col = m_whiteRook1.x();
    int rook1Rank = m_whiteRook1.y();
    int knight2Col = m_whiteKnight2.x();
    int knight2Rank = m_whiteKnight2.y();
    int bishop2Col = m_whiteBishop2.x();
    int bishop2Rank = m_whiteBishop2.y();
    int rook2Col = m_whiteRook2.x();
    int rook2Rank = m_whiteRook2.y();
    int pawn1Col = m_whitePawn1.x();
    int pawn1Rank = m_whitePawn1.y();
    int pawn2Col = m_whitePawn2.x();
    int pawn2Rank = m_whitePawn2.y();
    int pawn3Col = m_whitePawn3.x();
    int pawn3Rank = m_whitePawn3.y();
    int pawn4Col = m_whitePawn4.x();
    int pawn4Rank = m_whitePawn4.y();
    int pawn5Col = m_whitePawn5.x();
    int pawn5Rank = m_whitePawn5.y();
    int pawn6Col = m_whitePawn6.x();
    int pawn6Rank = m_whitePawn6.y();
    int pawn7Col = m_whitePawn7.x();
    int pawn7Rank = m_blackPawn7.y();
    int pawn8Col = m_blackPawn8.x();
    int pawn8Rank = m_blackPawn8.y();
    return kingSurvives(kingCol, kingRank, whiteKingCol, whiteKingRank, queenCol, queenRank, knight1Col, knight1Rank, bishop1Col, bishop1Rank, rook1Col, rook1Rank)
        || kingSurvives(kingCol, kingRank, whiteKingCol, whiteKingRank, queenCol, queenRank, knight2Col, knight2Rank, bishop2Col, bishop2Rank, rook2Col, rook2Rank)
        || kingSurvivesPawns(kingCol,kingRank,pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
}
bool ChessLivrable::kingSurvivesPawns(int kingCol, int kingRank,int pawn1Col, int pawn1Rank, int pawn2Col, int pawn2Rank, int pawn3Col,int pawn3Rank, int pawn4Col, int pawn4Rank, int pawn5Col, int pawn5Rank, int pawn6Col, int pawn6Rank, int pawn7Col, int pawn7Rank, int pawn8Col, int pawn8Rank)const {
    bool test = false;
    int rankTo = kingRank;
    int colTo = kingCol;

    test |= !kingEatenByPawns( colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);

    rankTo = kingRank - 1;
    colTo = kingCol;
    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    rankTo = kingRank + 1;
    colTo = kingCol;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    rankTo = kingRank;
    colTo = kingCol - 1;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    rankTo = kingRank;
    colTo = kingCol + 1;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    rankTo = kingRank - 1;
    colTo = kingCol + 1;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    rankTo = kingRank + 1;
    colTo = kingCol - 1;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    rankTo = kingRank + 1;
    colTo = kingCol + 1;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    rankTo = kingRank - 1;
    colTo = kingCol - 1;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEatenByPawns(colTo, rankTo, pawn1Col, pawn1Rank, pawn2Col, pawn2Rank, pawn3Col, pawn3Rank, pawn4Col, pawn4Rank, pawn5Col, pawn5Rank, pawn6Col, pawn6Rank, pawn7Col, pawn7Rank, pawn8Col, pawn8Rank);
    };

    return test;
};
bool ChessLivrable::kingEatenByPawns(int colTo, int rankTo, int pawn1Col, int pawn1Rank, int pawn2Col, int pawn2Rank, int pawn3Col, int pawn3Rank, int pawn4Col, int pawn4Rank, int pawn5Col, int pawn5Rank, int pawn6Col, int pawn6Rank, int pawn7Col, int pawn7Rank, int pawn8Col, int pawn8Rank)const {
    bool test = false;
    test |= pawnEats(rankTo - pawn1Rank, colTo - pawn1Col);
    test |= pawnEats(rankTo - pawn2Rank, colTo - pawn2Col);
    test |= pawnEats(rankTo - pawn3Rank, colTo - pawn3Col);
    test |= pawnEats(rankTo - pawn4Rank, colTo - pawn4Col);
    test |= pawnEats(rankTo - pawn5Rank, colTo - pawn5Col);
    test |= pawnEats(rankTo - pawn6Rank, colTo - pawn6Col);
    test |= pawnEats(rankTo - pawn7Rank, colTo - pawn7Col);
    test |= pawnEats(rankTo - pawn8Rank, colTo - pawn8Col);
    return test;
}
bool ChessLivrable::pawnEats(int rankDelta, int colDelta)const {
    bool test = false;
    int i=0;
    if (currentPlayer() == PlayerDark)i = 1;
    if (currentPlayer() == PlayerWhite)i = -1;
    if (abs(colDelta)==1&&rankDelta==i) {
        test = true;
    };
    return test;
}

bool ChessLivrable::kingEats(int rankDelta, int colDelta) const {
    bool test = false;
    if ((abs(rankDelta) == 0 && abs(colDelta) == 1) 
        || (abs(rankDelta) == 1 && abs(colDelta) == 0) 
        || (abs(rankDelta) == 1 && abs(colDelta) == 1)) {
        test= true;
    };
    return test;
}
bool ChessLivrable::knightEats(int rankDelta, int colDelta)const {
    bool test = false;
    if ((abs(rankDelta) == 2 && abs(colDelta) == 1) || (abs(rankDelta) == 1 && abs(colDelta) == 2)) {
        test = true;
    };
    return test;
    
};
bool ChessLivrable::queenEats(int rankDelta, int colDelta, int rankFrom, int colFrom)const {
    bool test = false;
    if (rankDelta == colDelta && rankDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom + counter, rankFrom + counter);
            if (destination != ' ') {
                test = false;
            };
        };

    }
    else if (rankDelta == colDelta && rankDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom - counter, rankFrom - counter);
            if (destination != ' ') {
                test = false;
            };
        };
    }
    else if (rankDelta == -colDelta && rankDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom - counter, rankFrom + counter);
            if (destination != ' ') {
                test = false;
            };
        };
    }
    else if (rankDelta == -colDelta && rankDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom + counter, rankFrom - counter);
            if (destination != ' ') {
                test = false;
            };
        };
    }
    else if(rankDelta == 0 && colDelta != 0 && colDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(colDelta); counter++) {
            char destination = board()->data(colFrom + counter, rankFrom);
            if (destination != ' ') {
                test = false;
            };
        };
    }
    else if (rankDelta == 0 && colDelta != 0 && colDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(colDelta); counter++) {
            char destination = board()->data(colFrom - counter, rankFrom);
            if (destination != ' ') {
                test = false;
            };
        };
    }
    else if (rankDelta != 0 && colDelta == 0 && rankDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom, rankFrom + counter);
            if (destination != ' ') {
                test = false;
            };
        };
    }
    else if (rankDelta != 0 && colDelta == 0 && rankDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom, rankFrom - counter);
            if (destination != ' ') {
                test = false;
            };
        };
    }
    else {
        test = false; // move is not vertical or horizontal or diagonal
    };
    return test;
}
bool ChessLivrable::bishopEats(int rankDelta, int colDelta,int rankFrom,int colFrom ) const{
    bool test = false;
    if (rankDelta == colDelta && rankDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom + counter, rankFrom + counter);
            if (destination != ' ') {
                test= false;
            };
        };

    }
    else if (rankDelta == colDelta && rankDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom - counter, rankFrom - counter);
            if (destination != ' ') {
                test= false;
            };
        };
    }
    else if (rankDelta == -colDelta && rankDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom - counter, rankFrom + counter);
            if (destination != ' ') {
                test= false;
            };
        };
    }
    else if (rankDelta == -colDelta && rankDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom + counter, rankFrom - counter);
            if (destination != ' ') {
                test= false;
            };
        };
    }
    else {
        test=false; // move is not diagonal
    };
    return test;
}
bool ChessLivrable::rookEats(int rankDelta, int colDelta, int rankFrom, int colFrom) const {
    bool test = false;
    if (rankDelta == 0 && colDelta != 0 && colDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(colDelta); counter++) {
            char destination = board()->data(colFrom + counter, rankFrom);
            if (destination != ' ') {
                test= false;
            };
        };
    }
    else if (rankDelta == 0 && colDelta != 0 && colDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(colDelta); counter++) {
            char destination = board()->data(colFrom - counter, rankFrom);
            if (destination != ' ') {
                test= false;
            };
        };
    }
    else if (rankDelta != 0 && colDelta == 0 && rankDelta > 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom, rankFrom + counter);
            if (destination != ' ') {
                test= false;
            };
        };
    }
    else if (rankDelta != 0 && colDelta == 0 && rankDelta < 0) {
        test = true;
        for (int counter = 1; counter < abs(rankDelta); counter++) {
            char destination = board()->data(colFrom, rankFrom - counter);
            if (destination != ' ') {
                test= false;
            };
        };
    }
    else {
        test= false; // move is not vertical or horizontal
    };
    return test;
}
bool ChessLivrable::kingEaten(int rankTo, int colTo, int oppositeKingCol, int oppositeKingRank, int queenCol, int queenRank, int knightCol, int knightRank, int bishopCol, int bishopRank, int rookCol, int rookRank)const {
    bool test = false;
    char destinationTest= board()->data(colTo, rankTo);
    test |= kingEats(rankTo - oppositeKingRank, colTo - oppositeKingCol);
    test |= knightEats(rankTo - knightRank, colTo - knightCol);
    test |= bishopEats(rankTo - bishopRank, colTo - bishopCol, bishopRank, bishopCol);
    test |= queenEats(rankTo - queenRank, colTo - queenCol, queenRank, queenCol);
    test |= rookEats(rankTo - rookRank, colTo - rookCol, rookRank, rookCol);
    if (currentPlayer() == PlayerWhite) {
        test |= (destinationTest=='Q'|| destinationTest=='N'|| destinationTest=='B'|| destinationTest=='R');
    };
    if (currentPlayer() == PlayerDark) {
        test |= (destinationTest == 'q' || destinationTest == 'n' || destinationTest == 'b' || destinationTest == 'r');
    };
    return test;
}
bool ChessLivrable::kingSurvives(int kingCol, int kingRank, int oppositeKingCol, int oppositeKingRank, int queenCol, int queenRank, int knightCol, int knightRank, int bishopCol, int bishopRank, int rookCol, int rookRank) const {
    bool test = false;
    int rankTo = kingRank;
    int colTo = kingCol;
    
    test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    
    rankTo = kingRank - 1;
    colTo = kingCol;
    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };

    rankTo = kingRank + 1;
    colTo = kingCol;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };

    rankTo = kingRank;
    colTo = kingCol - 1;
    
    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
       test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };

    rankTo = kingRank;
    colTo = kingCol + 1;

    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };

    rankTo = kingRank - 1;
    colTo = kingCol + 1;
    
    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };
    
    rankTo = kingRank + 1;
    colTo = kingCol - 1;
    
    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };
    
    rankTo = kingRank + 1;
    colTo = kingCol + 1;
    
    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };
    
    rankTo = kingRank - 1;
    colTo = kingCol - 1;
    
    if (0 < rankTo && rankTo < 9 && 0 < colTo && colTo < 9) {
        test |= !kingEaten(rankTo, colTo, oppositeKingCol, oppositeKingRank, queenCol, queenRank, knightCol, knightRank, bishopCol, bishopRank, rookCol, rookRank);
    };
    
    return test;
}