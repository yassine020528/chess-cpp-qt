#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Chess.h"
#include "ChessAlgorithm.h"
#include "ChessView.h"
#include"ChessGame.h"
#include "qlayout.h"
class ChessWindow : public QMainWindow
{
    Q_OBJECT

public:
    ChessWindow(QWidget *parent = nullptr );
    ~ChessWindow();
public slots:
    void viewClicked(const QPoint& field);
private:
    Ui::ChessClass ui;
    ChessView* m_view;
    ChessAlgorithm* m_algorithm;
    QPoint m_clickPoint;
    ChessView::FieldHighlight* m_selectedField;
};
