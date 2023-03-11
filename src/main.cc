#include <QApplication>

#include "controller/controller.h"
#include "model/model.h"
#include "view/mainviewer.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  Model model;
  Controller controller(&model);
  MainViewer w(&controller);
  w.show();
  return a.exec();
}
