#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSlider;
class QComboBox;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    // اکولایزر
    QList<QSlider*> sliders;
    QPushButton *enableButton;
    QComboBox *presetCombo;

    // ولوم و میوت
    QSlider *volumeSlider;
    QPushButton *muteButton;
    bool muted = false;
    int lastVolume = 50; // حجم آخر قبل از میوت

    // دکمه پنجره پیشرفته
    QPushButton *advancedButton;

    // ---------- flag برای جلوگیری از loop در preset ----------
    bool presetChanging = false;
private slots:
    void toggleEnable();
    void presetChanged(int index);
    void toggleMute();
    void openAdvancedWindow();
    void volumeChanged(int value);
};

#endif // MAINWINDOW_H

