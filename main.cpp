#include <QApplication>

#include "sfo.h"
#include "appinfo.h"

int main(int argc, char *argv[]) {
  // This function must be called before creating the QGuiApplication object
  QApplication::setDesktopSettingsAware(true);

  QApplication app(argc, argv);
  app.setApplicationName(applicationName);
  app.setApplicationVersion(applicationVersion);
  app.setWindowIcon(QIcon(":/res/logo/SFO_v2.ico"));
  app.setApplicationDisplayName(applicationDisplayName);
  app.setEffectEnabled(Qt::UI_AnimateMenu, true);

  sfo window;
  window.setWindowTitle(applicationDisplayName);
  window.setMinimumSize(minAppSize);
  window.setAcceptDrops(false);
  window.setDisabled(false);
  window.show();

  return app.exec();
}
