#ifndef L_tmpnam
#define L_tmpnam 20
#endif
#include <cstdio>
#include "mainwindow.h"
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    // ----------------- کنترل Enable/Disable -----------------
    enableButton = new QPushButton("Enable", this);
    enableButton->setCheckable(true);
    connect(enableButton, &QPushButton::clicked, this, &MainWindow::toggleEnable);
    mainLayout->addWidget(enableButton);

    // ----------------- کنترل Preset -----------------
    presetCombo = new QComboBox(this);
    presetCombo->addItems({"Rock", "Pop", "Classic", "Flat", "Custom"});
    connect(presetCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::presetChanged);
    mainLayout->addWidget(presetCombo);

    // ----------------- 10 باند اکولایزر -----------------
    QHBoxLayout *hLayout = new QHBoxLayout();
    mainLayout->addLayout(hLayout);

    QStringList freqs = {"31Hz","62Hz","125Hz","250Hz","500Hz",
                         "1kHz","2kHz","4kHz","8kHz","16kHz"};

    presetChanging = false; // flag برای جلوگیری از loop

    for(int i = 0; i < 10; ++i) {
        QVBoxLayout *vLayout = new QVBoxLayout();

        QLabel *label = new QLabel(freqs[i], this);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);

        QSlider *slider = new QSlider(Qt::Vertical, this);
        slider->setMinimum(-12);
        slider->setMaximum(12);
        slider->setValue(0);
        slider->setEnabled(false);

        // تغییر دستی کاربر باعث تغییر به Custom می‌شود
        connect(slider, &QSlider::actionTriggered, [this](int){
            if(!presetChanging && presetCombo->currentText() != "Custom") {
                presetChanging = true;
                presetCombo->setCurrentText("Custom");
                presetChanging = false;
                qDebug() << "Switched to Custom mode due to manual change";
            }
        });

        connect(slider, &QSlider::valueChanged, [i](int value){
            qDebug("Band %d value: %d", i+1, value);
        });

        vLayout->addWidget(label);
        vLayout->addWidget(slider);

        sliders.append(slider);
        hLayout->addLayout(vLayout);
    }

    // ----------------- کنترل ولوم و میوت -----------------
    QHBoxLayout *volumeLayout = new QHBoxLayout();
    QLabel *volLabel = new QLabel("Volume:", this);
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(lastVolume);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainWindow::volumeChanged);

    muteButton = new QPushButton("Mute", this);
    muteButton->setCheckable(true);
    connect(muteButton, &QPushButton::clicked, this, &MainWindow::toggleMute);

    volumeLayout->addWidget(volLabel);
    volumeLayout->addWidget(volumeSlider);
    volumeLayout->addWidget(muteButton);

    mainLayout->addLayout(volumeLayout);

    // ----------------- دکمه پنجره پیشرفته -----------------
    advancedButton = new QPushButton("Advanced", this);
    connect(advancedButton, &QPushButton::clicked, this, &MainWindow::openAdvancedWindow);
    mainLayout->addWidget(advancedButton);
}

MainWindow::~MainWindow() {}

void MainWindow::toggleEnable()
{
    bool enabled = enableButton->isChecked();
    enableButton->setText(enabled ? "Disable" : "Enable");

    // فعال/غیرفعال کردن همه اسلایدرها
    for (QSlider *s : sliders) {
        s->setEnabled(enabled);
    }

    // فعال/غیرفعال کردن ComboBox و سایر کنترل‌ها
    presetCombo->setEnabled(enabled);
    advancedButton->setEnabled(enabled);   // اضافه شد ✅

    qDebug() << "Equalizer" << (enabled ? "Enabled" : "Disabled");
}

void MainWindow::presetChanged(int index)
{
    if(presetChanging) return;

    presetChanging = true;

    QString preset = presetCombo->itemText(index);
    qDebug() << "Preset changed to:" << preset;

    if(preset == "Rock") { int vals[10]={5,4,3,2,1,0,1,2,3,4}; for(int i=0;i<10;i++) sliders[i]->setValue(vals[i]); }
    else if(preset == "Pop") { int vals[10]={0,2,4,6,4,2,0,-2,-4,-6}; for(int i=0;i<10;i++) sliders[i]->setValue(vals[i]); }
    else if(preset == "Classic") { int vals[10]={3,2,1,0,0,1,2,3,4,5}; for(int i=0;i<10;i++) sliders[i]->setValue(vals[i]); }
    else if(preset == "Flat") { for(QSlider *s: sliders) s->setValue(0); }
    // Custom: بدون تغییر

    presetChanging = false;
}

void MainWindow::toggleMute()
{
    muted = muteButton->isChecked();
    if (muted) {
        lastVolume = volumeSlider->value();   // ذخیره ولوم فعلی
        volumeSlider->setValue(0);            // صفر کردن
        volumeSlider->setEnabled(false);      // 🚫 غیرفعال کردن اسلایدر
        muteButton->setText("Unmute");
    } else {
        volumeSlider->setValue(lastVolume);   // بازیابی ولوم
        volumeSlider->setEnabled(true);       // ✅ فعال کردن اسلایدر
        muteButton->setText("Mute");
    }
    qDebug() << (muted ? "Muted" : "Unmuted");
}


void MainWindow::volumeChanged(int value)
{
    if(!muted) {
        qDebug() << "Volume changed to:" << value;
    }
}

void MainWindow::openAdvancedWindow()
{
    QMessageBox::information(this, "Advanced", "Advanced window would open here!");
    // در اینجا می‌توانید QWidget یا QDialog پیشرفته باز کنید
}
