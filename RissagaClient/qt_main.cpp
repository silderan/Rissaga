#undef main
/*
#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
*/

#include "SDL.h"

int main()
{
  SDL_Init(SDL_INIT_VIDEO);
  return 0;
}
