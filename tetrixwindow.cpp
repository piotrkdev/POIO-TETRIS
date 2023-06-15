#include "tetrixboard.h"
#include "tetrixwindow.h"

#include <QCoreApplication>
#include <QGridLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>

//! [0]
TetrixWindow::TetrixWindow(QWidget *parent)
    : QWidget(parent), board(new TetrixBoard)
{
    //! [0]
    nextPieceLabel = new QLabel;
    nextPieceLabel->setFrameStyle(QFrame::Box | QFrame::Raised);
    nextPieceLabel->setAlignment(Qt::AlignCenter);
    board->setNextPieceLabel(nextPieceLabel);
    //! [1]
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    //! [1]
    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    //! [2]
    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton(tr("&Pauza"));
    //! [2] //! [3]
    pauseButton->setFocusPolicy(Qt::NoFocus);
    //! [3] //! [4]

    connect(startButton, &QPushButton::clicked, board, &TetrixBoard::start);
    //! [4] //! [5]
    connect(quitButton , &QPushButton::clicked, qApp, &QCoreApplication::quit);
    connect(pauseButton, &QPushButton::clicked, board, &TetrixBoard::pause);
    connect(board, &TetrixBoard::scoreChanged,
            scoreLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::levelChanged,
            levelLcd, qOverload<int>(&QLCDNumber::display));
    connect(board, &TetrixBoard::linesRemovedChanged,
            linesLcd, qOverload<int>(&QLCDNumber::display));
    //! [5]

    //! [6]
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 0, 0, 8, 2);
    layout->addWidget(createLabel(tr("Następny klocek")), 0, 2);
    layout->addWidget(nextPieceLabel, 1, 2);
    layout->addWidget(createLabel(tr("Wynik")), 2, 2);
    layout->addWidget(scoreLcd, 3, 2);
    layout->addWidget(createLabel(tr("Usunięte linijki")), 4, 2);
    layout->addWidget(linesLcd, 5, 2);
    layout->addWidget(startButton, 6, 2);
    layout->addWidget(pauseButton, 7, 2);
    setLayout(layout);

    setWindowTitle(tr("Tetris"));
    resize(350, 400);
}
//! [6]

//! [7]
QLabel *TetrixWindow::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
//! [7]
