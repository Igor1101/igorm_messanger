#ifndef CONSOLEREADER_H
#define CONSOLEREADER_H

#include <QThread>
#include <ncurses.h>
extern WINDOW *window;
class ConsoleReader : public QThread
{
    Q_OBJECT
signals:
    void KeyPressed(char ch);
public:
   ConsoleReader();
   ~ConsoleReader();
   void run();
};

#endif  /* CONSOLEREADER_H */
