#ifndef SRC_BORDER_H_
#define SRC_BORDER_H_
#include <QColorDialog>
#include <QDialog>
#include <QPalette>

namespace Ui {
class Border;
}

class Border : public QDialog {
  Q_OBJECT

 public:
  explicit Border(QWidget *parent = nullptr);
  void SetBorderType(int value);
  void SetBorderThickness(double value);
  void SetBorderColor(double red, double green, double blue);
  ~Border();

 signals:
  void signalBorderColor(double red, double green, double blue);
  void signalBorderThickness(double thickness_border);
  void signalBorderType(int type_border);

 private slots:
  void on_apply_border_clicked();
  void on_color_border_clicked();
  void on_thickness_border_valueChanged(double arg1);
  void on_type_border_currentIndexChanged(int index);

 private:
  const QString style_sheet_ =
      "background-color: %1;\nborder: 1px solid gray;\nborder-radius: 5px;";
  float red_{};
  float green_{};
  float blue_{};
  double thickness_border_{};
  int type_border_{};
  QColor color_border_;
  Ui::Border *ui;
};

#endif  // SRC_BORDER_H_
