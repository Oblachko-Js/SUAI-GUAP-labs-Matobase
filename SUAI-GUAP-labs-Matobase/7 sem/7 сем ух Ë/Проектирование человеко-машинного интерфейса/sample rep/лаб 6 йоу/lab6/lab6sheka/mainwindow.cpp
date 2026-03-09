#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QDateTime>
#include <QPainter>
#include <QVideoFrame>
#include <QDebug>
#include <QThread>
#include <QProcess>
#include <QFileDialog>
#include <QMessageBox>>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Настройка сцены
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    setupScene();

    // Настройка анимации
    animation = new QPropertyAnimation(this, "currentFrame", this);
    animation->setDuration(5000);
    animation->setStartValue(0);
    animation->setEndValue(100);
    animation->setLoopCount(1);

    connect(this, &MainWindow::currentFrameChanged, this, &MainWindow::updateAnimation);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::currentFrame() const
{
    return m_currentFrame;
}

void MainWindow::setCurrentFrame(int frame)
{
    if (m_currentFrame != frame) {
        m_currentFrame = frame;
        emit currentFrameChanged(frame);
    }
}

void MainWindow::setupScene()
{
    scene->clear();

    // Создание объектов
    rectangle = new QGraphicsRectItem(-50, -50, 100, 100);
    rectangle->setBrush(Qt::blue);
    rectangle->setPos(200, 150);

    circle = new QGraphicsEllipseItem(-40, -40, 80, 80);
    circle->setBrush(Qt::red);
    circle->setPos(400, 250);

    scene->addItem(rectangle);
    scene->addItem(circle);
    scene->setSceneRect(0, 0, 600, 400);

    // Начальные ключевые кадры
    keyframes.clear();
    scales.clear();

    // Ключевой кадр 1
    keyframes.append(QPointF(200, 150));
    scales.append(1.0);

    // Ключевой кадр 2
    keyframes.append(QPointF(400, 250));
    scales.append(1.5);

    // Ключевой кадр 3
    keyframes.append(QPointF(300, 200));
    scales.append(0.8);

    // Ключевой кадр 4 (возврат к началу)
    keyframes.append(QPointF(200, 150));
    scales.append(1.0);
}

void MainWindow::updateAnimation()
{
    if (keyframes.size() < 2) return;

    float progress = m_currentFrame / 100.0f;
    int totalSegments = keyframes.size() - 1;
    int segment = progress * totalSegments;

    if (segment >= totalSegments) {
        segment = totalSegments - 1;
    }

    float t = (progress * totalSegments) - segment;

    // Интерполяция положения
    QPointF pos = keyframes[segment] * (1 - t) + keyframes[segment + 1] * t;

    // Интерполяция масштаба
    qreal scale = scales[segment] * (1 - t) + scales[segment + 1] * t;

    rectangle->setPos(pos);
    rectangle->setScale(scale);

    // Движение круга в противоположном направлении
    circle->setPos(600 - pos.x(), 400 - pos.y());
    circle->setScale(2.0 - scale);

    ui->statusbar->showMessage(QString("Кадр: %1, Прогресс: %2%").arg(m_currentFrame).arg(progress * 100, 0, 'f', 1));
}

void MainWindow::on_btnPlay_clicked()
{
    animation->start();
}

void MainWindow::on_btnAddKeyframe_clicked()
{
    // Добавление текущего положения как ключевого кадра
    keyframes.append(rectangle->pos());
    scales.append(rectangle->scale());

    ui->statusbar->showMessage(QString("Добавлен ключевой кадр. Всего: %1").arg(keyframes.size()));

    // Обновляем конечное значение анимации
    animation->setEndValue(keyframes.size() * 25);
}

void MainWindow::on_btnRender_clicked()
{
    // Выбор папки для сохранения
    QString saveDir = QFileDialog::getExistingDirectory(this, "Выберите папку для сохранения", QDir::homePath());
    if (saveDir.isEmpty()) return;

    QString videoPath = saveDir + "/output.mp4";
    QString framesDir = saveDir + "/frames";

    ui->statusbar->showMessage("Начало рендеринга...");
    QApplication::processEvents();

    // Создаем папку для кадров
    QDir dir(framesDir);
    if (!dir.exists()) {
        dir.mkpath(".");
    } else {
        // Очищаем папку
        dir.setNameFilters(QStringList() << "*.png");
        dir.setFilter(QDir::Files);
        foreach(QString dirFile, dir.entryList()) {
            dir.remove(dirFile);
        }
    }

    // Фиксированный размер для видео (должен быть делимым на 2)
    QSize videoSize(800, 600);

    // Сохраняем кадры анимации с фиксированным размером
    for (int i = 0; i <= 100; ++i) {
        setCurrentFrame(i);
        updateAnimation();

        // Ждем немного для обновления UI
        QApplication::processEvents();
        QThread::msleep(10);

        // Создаем изображение с фиксированным размером
        QPixmap pixmap(videoSize);
        pixmap.fill(Qt::white);
        QPainter painter(&pixmap);

        // Масштабируем рендер под нужный размер
        QRect targetRect(0, 0, videoSize.width(), videoSize.height());
        QRect sourceRect = ui->graphicsView->sceneRect().toRect(); // Конвертируем QRectF в QRect
        ui->graphicsView->render(&painter, targetRect, sourceRect);

        // Сохраняем кадр
        QString filename = QString("%1/frame_%2.png").arg(framesDir).arg(i, 3, 10, QChar('0'));
        if (pixmap.save(filename)) {
            qDebug() << "Сохранен кадр:" << filename;
        } else {
            qDebug() << "Ошибка сохранения:" << filename;
        }
    }

    ui->statusbar->showMessage("Создание видео...");
    QApplication::processEvents();

    // Явно указываем путь к ffmpeg на macOS
    QString ffmpegCommand = "/opt/homebrew/bin/ffmpeg";

    // Проверяем, существует ли ffmpeg
    if (!QFile::exists(ffmpegCommand)) {
        QMessageBox::warning(this, "Ошибка",
                             "FFmpeg не найден по пути: /opt/homebrew/bin/ffmpeg\n\n"
                             "Установите: brew install ffmpeg");
        return;
    }

    QProcess process;

    // Устанавливаем рабочую директорию, чтобы пути были относительными
    process.setWorkingDirectory(saveDir);

    QStringList arguments;
    arguments << "-r" << "20"
              << "-i" << "frames/frame_%03d.png"
              << "-c:v" << "libx264"
              << "-pix_fmt" << "yuv420p"
              << "-y"
              << "output.mp4";

    qDebug() << "Запуск FFmpeg:" << ffmpegCommand << arguments;

    process.start(ffmpegCommand, arguments);

    if (process.waitForStarted()) {
        if (process.waitForFinished(30000)) {
            if (process.exitCode() == 0) {
                // Проверяем, что файл действительно создался
                if (QFile::exists(videoPath)) {
                    ui->statusbar->showMessage(QString("Видео успешно создано: %1").arg(videoPath));
                    QMessageBox::information(this, "Успех", QString("Видео сохранено:\n%1").arg(videoPath));

                    // Открываем папку с видео (только на macOS)
#ifdef Q_OS_MAC
                    QProcess::execute("open", QStringList() << "-R" << videoPath);
#endif
                } else {
                    ui->statusbar->showMessage("Видеофайл не создан");
                    QMessageBox::warning(this, "Ошибка",
                                         "FFmpeg завершился успешно, но видеофайл не был создан.\n"
                                         "Проверьте права доступа к папке.");
                }
            } else {
                QString errorOutput = process.readAllStandardError();
                ui->statusbar->showMessage("Ошибка при создании видео");
                QMessageBox::warning(this, "Ошибка",
                                     QString("Ошибка FFmpeg:\n%1").arg(errorOutput));
            }
        } else {
            ui->statusbar->showMessage("Таймаут создания видео");
            QMessageBox::warning(this, "Ошибка", "Превышено время создания видео.");
        }
    } else {
        ui->statusbar->showMessage("Не удалось запустить FFmpeg");
        QMessageBox::warning(this, "Ошибка",
                             QString("Не удалось запустить FFmpeg:\n%1\n\n"
                                     "Проверьте установку: brew install ffmpeg")
                                 .arg(process.errorString()));
    }
}
