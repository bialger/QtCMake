#include <iostream>

#include <QApplication>
#include <QDateTime>
#include <QLCDNumber>
#include <QTimer>

namespace {
static constexpr int kInterval = 1000;
static constexpr int kDigitCount = 8;
static constexpr int kWidth = 280;
static constexpr int kHeight = 100;
static constexpr const char* kFormat = "hh:mm:ss";
} // namespace

int main(int argc, char** argv) {
  if (argc > 1) {
    std::cout << "No CLI arguments allowed.\n";
    return 0;
  }

  QApplication a(argc, argv);

  QLCDNumber lcd;
  QTimer t;
  QObject::connect(&t, &QTimer::timeout, [&lcd]() { lcd.display(QDateTime::currentDateTime().toString(kFormat)); });
  t.start(kInterval);
  lcd.setDigitCount(kDigitCount);
  lcd.display(QDateTime::currentDateTime().toString(kFormat));
  lcd.resize(kWidth, kHeight);
  lcd.show();

  return QApplication::exec();
}
