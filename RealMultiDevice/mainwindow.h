#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "stdafx.h"
#include <QMainWindow>
#include <QWidget>
#include <QString>

typedef wchar_t* LPWSTR, *PWSTR;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void DisplayFriendlyName(
            _In_ IPortableDeviceManager* deviceManager,
            _In_ PCWSTR                   pnpDeviceID);

    DWORD EnumerateAllDevices();
protected:
    wchar_t* showName;
    wchar_t* showManufacturer = nullptr;
    wchar_t* showDescription = nullptr;
private slots:
    void on_RefreshBtn_clicked();

    void on_AddBtn_clicked();

    void on_TargetPathBtn_clicked();

private:
    Ui::MainWindow *ui;
    QString targetFolderName;

};

#endif // MAINWINDOW_H
