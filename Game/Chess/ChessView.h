#pragma once
#ifndef CHESSVIEW_H
#define CHESSVIEW_H

#include <QWidget>
#include <QPointer>
#include <QFontMetrics>
#include <QMouseEvent>
#include "ChessBoard.h"
#include "qpainter.h"

class ChessView : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(ChessBoard* board READ board WRITE setBoard NOTIFY boardChanged)
        Q_PROPERTY(QSize fieldSize
            READ fieldSize WRITE setFieldSize
            NOTIFY fieldSizeChanged)

public:
    class Highlight {
    public:
        Highlight() {}
        virtual ~Highlight() {}
        virtual int type() const { return 0; }
    };
    class FieldHighlight : public Highlight {
    public:
        enum { Type = 1 };
        FieldHighlight(int column, int rank, QColor color)
            : m_field(column, rank), m_color(color) {}
        inline int column() const { return m_field.x(); }
        inline int rank() const { return m_field.y(); }
        inline QColor color() const { return m_color; }
        int type() const { return Type; }
    private:
        QPoint m_field;
        QColor m_color;
    };
    void addHighlight(Highlight* hl);
    void removeHighlight(Highlight* hl);
    inline Highlight* highlight(int index) const {
        return m_highlights.at(index);
    }
    inline int highlightCount() const {
        return m_highlights.size();
    }
    virtual void drawHighlights(QPainter* painter);
    ChessView(QWidget* parent = nullptr);
    ChessBoard* board() const;
    void setFieldSize(QSize arg);
    QSize fieldSize() const;
    QSize sizeHint() const;
    QRect fieldRect(int column, int rank) const;
    void paintEvent(QPaintEvent*);
    void setPiece(char type, const QIcon& icon);
    QIcon piece(char type) const;
    virtual void drawPiece(QPainter* painter, int column, int rank);
    QPoint fieldAt(const QPoint& pt) const;
    void mouseReleaseEvent(QMouseEvent* event) override;

public slots:
    void setBoard(ChessBoard* board);

signals:
    void clicked(const QPoint&);
    void boardChanged(ChessBoard* board);
    void fieldSizeChanged(QSize arg);
protected:
    virtual void drawRank(QPainter* painter, int rank);
    virtual void drawColumn(QPainter* painter, int column);
    virtual void drawField(QPainter* painter, int column, int rank);
private:
    QSize m_fieldSize;
    QPointer<ChessBoard> m_board;
    QMap<char, QIcon> m_pieces;
    QList<Highlight*> m_highlights;
};

#endif // CHESSVIEW_H
