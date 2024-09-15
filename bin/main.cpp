#include <iostream>

#include <QApplication>
#include <QLCDNumber>
#include <QTimer>
#include <QDateTime>

int main(int argc, char* argv[]) {
  if (argc > 1) {
    std::cout << "No CLI arguments allowed." << std::endl;
    return 0;
  }

  QApplication a(argc, argv);

  QLCDNumber lcd;
  QTimer t;
  QObject::connect(&t,
                   &QTimer::timeout,
                   [&lcd]() {
                     lcd.display(QDateTime::currentDateTime().toString("hh:mm:ss"));
                   });
  t.start(1000);
  lcd.setDigitCount(8);
  lcd.display(QDateTime::currentDateTime().toString("hh:mm:ss"));
  lcd.resize(280, 100);
  lcd.show();

  return a.exec();
}
