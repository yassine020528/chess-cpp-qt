#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ChessTest.h"
#include "ChessAlgorithm.h"
#include "ChessView.h"
#include"ChessLivrable.h"
#include "qlayout.h"
class ChessTest : public QMainWindow
{
    Q_OBJECT

public:
    ChessTest(QWidget *parent = nullptr );
    ~ChessTest();
public slots:
    void viewClicked(const QPoint& field);
private:
    Ui::ChessTestClass ui;
    ChessView* m_view;
    ChessAlgorithm* m_algorithm;
    QPoint m_clickPoint;
    ChessView::FieldHighlight* m_selectedField;
};
