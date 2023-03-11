#ifndef SRC_PERSPECTIVE_H_
#define SRC_PERSPECTIVE_H_

#include <QDialog>

namespace Ui {
class Perspective;
}

class Perspective : public QDialog {
  Q_OBJECT

 public:
  explicit Perspective(QWidget *parent = nullptr);
  ~Perspective();

 signals:
  void signalPerspectiveType(int perspective_type);

 private slots:
  void on_parallel_clicked();
  void on_central_clicked();

 private:
  Ui::Perspective *ui;
};

#endif  // SRC_PERSPECTIVE_H_
