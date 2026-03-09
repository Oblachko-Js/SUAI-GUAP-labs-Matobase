#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSplitter>
#include <QTabWidget>
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QCalendarWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QStandardItemModel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setupUI();

    QFileSystemModel *fileModel;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QListView *listView;
    QTableView *tableView;
    QTreeView *treeView;
    QCalendarWidget *calendarWidget;
    QGroupBox *groupBox;
    QButtonGroup *buttonGroup;
};

#endif // MAINWINDOW_H
