#include <QApplication>

#include "sfo.h"
#include "appinfo.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setApplicationName(applicationName);
  app.setApplicationVersion(applicationVersion);


  sfo window;
  window.setWindowTitle(applicationName);
  window.setMinimumSize(minAppSize);
  window.show();

  return app.exec();
}
