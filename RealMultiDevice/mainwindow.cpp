#include "stdafx.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <iostream>
#include <QList>
#include <QListWidget>
#include <QString>
#include <QtWidgets>
#include <ShlObj.h>
#include <QMessageBox>

using namespace std;
typedef wchar_t* LPWSTR, *PWSTR;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_RefreshBtn_clicked()
{
    ui->DeviceList->clear();
   cout << "Number of device: " << EnumerateAllDevices() << endl;
}

//Get all devices that are connected to the PC
DWORD MainWindow::EnumerateAllDevices(){
    DWORD pnpDeviceIDCount = 0;
    ComPtr<IPortableDeviceManager> deviceManager;

    HRESULT hr = CoCreateInstance(CLSID_PortableDeviceManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&deviceManager));
    cout << "hr = " << hr << endl;
    if (FAILED(hr)){
        cout << "Failed to CoCreateInstance CLSID_PortableDeviceManager, hr = " << hr << endl;
    }
    if (SUCCEEDED(hr)){
        hr = deviceManager->GetDevices(nullptr, &pnpDeviceIDCount);
        if (FAILED(hr)){
            cout << "Failed to get number of devices on the system" << endl;
        }
    }
    cout << " after getDevices hr = " << hr << endl;

    if (SUCCEEDED(hr) && (pnpDeviceIDCount > 0)){
        PWSTR* pnpDeviceIDs = new(std::nothrow) PWSTR[pnpDeviceIDCount];

        if (pnpDeviceIDs != nullptr){
            ZeroMemory(pnpDeviceIDs, pnpDeviceIDCount * sizeof(PWSTR));
            DWORD retrievedDeviceIDCount = pnpDeviceIDCount;
            hr = deviceManager->GetDevices(pnpDeviceIDs, &retrievedDeviceIDCount);

            if (SUCCEEDED(hr)){
                _Analysis_assume_(retrievedDeviceIDCount <= pnpDeviceIDCount);
                //for each device found, get and display the name, manufacturer and description
                for (DWORD index = 0; index < retrievedDeviceIDCount; index++){
                    cout << "Calling displays iteration: " << index << endl;
                    DisplayFriendlyName(deviceManager.Get(), pnpDeviceIDs[index]);
                  //  DisplayManufacturer(deviceManager.Get(), pnpDeviceIDs[index]);
                   // DisplayDescription(deviceManager.Get(), pnpDeviceIDs[index]);
                    //addToList(showName, showManufacturer, showDescription);
                }

            }
            else{
               cout << "Failed to get the device list from the system" << endl;
            }

            for (DWORD index = 0; index < pnpDeviceIDCount; index++){
                CoTaskMemFree(pnpDeviceIDs[index]);
                pnpDeviceIDs[index] = nullptr;
            }

            delete[] pnpDeviceIDs;
            pnpDeviceIDs = nullptr;

        }

    }
    else{
        QMessageBox::information(this, tr("Error"), tr("No Devices Found"));
        cout << "Failed to allocate memory for PWSTR array" << endl;
        cout << "Enum aLL dEVICES" << endl;

    }

    return pnpDeviceIDCount;
}


void MainWindow::DisplayFriendlyName( _In_ IPortableDeviceManager* deviceManager,
                                      _In_ PCWSTR                  pnpDeviceID){

    DWORD friendlyNameLength = 0;

                    HRESULT hr = deviceManager->GetDeviceFriendlyName(pnpDeviceID, nullptr, &friendlyNameLength);
                    if (FAILED(hr)){
                        cout << "Failed to get the number of characters for device friendly name, hr = " << hr << endl;
                    }//end if
                    else if (friendlyNameLength > 0){
                        cout << "before" << endl;

                        // PWSTR friendlyName = new(nothrow)WCHAR[friendlyNameLength];
                        wchar_t *friendlyName = new(nothrow)WCHAR[friendlyNameLength];
                        cout << "after" << endl;
                        if (friendlyName != nullptr){
                            cout << "in if part" << endl;

                           ZeroMemory(friendlyName, friendlyNameLength * sizeof(WCHAR));
                          //  memset(friendlyName, '\0', friendlyNameLength);
                            cout << "after zero memeory" << endl;

                            hr = deviceManager->GetDeviceFriendlyName(pnpDeviceID, friendlyName, &friendlyNameLength);
                            cout << "after hr" << endl;

                            if (SUCCEEDED(hr)){
                                //lstDeviceList->Items->Add(gcnew String(friendlyName));
                             //   cout << "Success Name is: " << friendlyName << endl;
                                wprintf(L"Friendly Name: %ws\n", friendlyName);

                                showName = friendlyName;

                                wprintf(L"Show Name version: %ws\n", showName);

                                QString qStr = QString::fromWCharArray(showName); //display the device name to the user
                            //    cout << "qStr: " << qStr << endl;

                               // CoTaskMemFree(static_cast<void*>(showName));

                              //  cout << "addToList: " << &friendlyName << endl;

                                ui->DeviceList->addItem(qStr);
                            }//end if
                            else{
                                cout << "Failed to get the friendly name" << hr << endl;
                            }//end else

                            delete[] friendlyName;
                            friendlyName = nullptr;
                        }//end if
                        else{
                            cout << "I skipped the if" << endl;
                        }
                    }//end else if

}//end function displayFriendlyName

void MainWindow::on_AddBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C://Users/dazma/Music",
                "Music File (*mp3)");

    ui->fileList->addItem(filename);

}

void MainWindow::on_TargetPathBtn_clicked()
{

}
