#include <QApplication>

#include "sfo.h"
#include "appinfo.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  app.setApplicationName(applicationName);
  app.setApplicationVersion(applicationVersion);
  app.setWindowIcon(QIcon(":/res/logo/SFO_v2.ico"));

  sfo window;
  window.setWindowTitle(applicationName);
  window.setMinimumSize(minAppSize);
  window.show();

  return app.exec();
}
