#include "ChessTest.h"

ChessTest::ChessTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_selectedField = nullptr;
    m_view = new ChessView;
    m_algorithm = new ChessLivrable(this);
    m_algorithm->newGame();
    m_view->setBoard(m_algorithm->board());
    setCentralWidget(m_view);
    m_view->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    m_view->setFieldSize(QSize(50, 50));
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    m_view->setPiece('P', QIcon("../../piecesImages/Chess_plt45.svg")); // pawn
    m_view->setPiece('K', QIcon("../../piecesImages/Chess_klt45.svg")); // king
    m_view->setPiece('Q', QIcon("../../piecesImages/Chess_qlt45.svg")); // queen
    m_view->setPiece('R', QIcon("../../piecesImages/Chess_rlt45.svg")); // rook
    m_view->setPiece('N', QIcon("../../piecesImages/Chess_nlt45.svg")); // knight
    m_view->setPiece('B', QIcon("../../piecesImages/Chess_blt45.svg")); // bishop

    m_view->setPiece('p', QIcon("../../piecesImages/Chess_pdt45.svg")); // pawn
    m_view->setPiece('k', QIcon("../../piecesImages/Chess_kdt45.svg")); // king
    m_view->setPiece('q', QIcon("../../piecesImages/Chess_qdt45.svg")); // queen
    m_view->setPiece('r', QIcon("../../piecesImages/Chess_rdt45.svg")); // rook
    m_view->setPiece('n', QIcon("../../piecesImages/Chess_ndt45.svg")); // knight
    m_view->setPiece('b', QIcon("../../piecesImages/Chess_bdt45.svg")); // bishop 
    connect(m_view, &ChessView::clicked,
        this, &ChessTest::viewClicked);
}

ChessTest::~ChessTest()
{}
void ChessTest::viewClicked(const QPoint& field)
{
    if (m_clickPoint.isNull()) {
        if (m_view->board()->data(field.x(), field.y()) != ' ') {
            m_clickPoint = field;
            m_selectedField = new ChessView::FieldHighlight(
                field.x(), field.y(), QColor(255, 0, 0, 50)
            );
            m_view->addHighlight(m_selectedField);
        }
    }
    else {
        if (field != m_clickPoint) {
            m_algorithm->move(m_clickPoint, field);
        };
        m_clickPoint = QPoint();
        m_view->removeHighlight(m_selectedField);
        delete m_selectedField;
        m_selectedField = nullptr;
    }
}
