#include "QuickOpenWindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDesktopServices>

QuickOpenWindow::QuickOpenWindow(QWidget *parent)
: QMainWindow(parent)
, ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _mainVerticalLayout = ui->verticalLayout;
    _mainVerticalLayout->setAlignment(Qt::AlignTop);

    ui->ConsoleText->setReadOnly(true);

    SetStyle();
    LoadJson();
}

QuickOpenWindow::~QuickOpenWindow()
{
    ClearOldItem();

    delete ui;
}

void
QuickOpenWindow::SetStyle()
{
    QFile styleFile(":/generalStyle.qss");
    styleFile.open(QFile::ReadOnly);
    if (styleFile.isOpen())
    {
        qApp->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
}

// Json
void
QuickOpenWindow::LoadJson()
{
    QFile jsonFile(qApp->applicationDirPath() + "/path.json");
    if(!jsonFile.open(QIODevice::ReadOnly))
    {
        auto btn = QMessageBox::information(this,"Error","Path Json Load Fail", QMessageBox::StandardButton::Ok);
        if (btn == QMessageBox::StandardButton::Ok)
            QApplication::exit();
        return;
    }

    QByteArray allData = jsonFile.readAll();
    jsonFile.close();

    QJsonParseError jsonError;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

    if(jsonError.error != QJsonParseError::NoError)
    {
        auto btn = QMessageBox::information(this,"Error",jsonError.errorString(), QMessageBox::StandardButton::Ok);
        if (btn == QMessageBox::StandardButton::Ok)
            QApplication::exit();
        return;
    }

    QJsonObject rootObj = jsonDoc.object();

    // Clear
    ClearOldItem();
    _mainVerticalLayout->removeWidget(ui->ConsoleText);

    if(rootObj.contains("path") && rootObj["path"].isArray())
    {
        QJsonArray subArray = rootObj.value("path").toArray();
        for (int i = 0; i< subArray.size(); i++)
        {
            QJsonObject oneProject = subArray[i].toObject();
            if (oneProject.contains("name")
            && oneProject.contains("basePath")
            && oneProject.contains("buttons")
            && oneProject["buttons"].isArray())
            {
                ProjectItem* projPtr = new ProjectItem(oneProject["name"].toString(), oneProject["basePath"].toString());
                _uiItemVec.push_back(projPtr);

                _mainVerticalLayout->addLayout(projPtr->GetOuterLayout());

                QJsonArray buttonRoot = oneProject["buttons"].toArray();
                for (int j = 0; j< buttonRoot.size(); j++)
                {
                    QJsonObject oneButton = buttonRoot[j].toObject();
                    if (oneButton.contains("buttonName") && oneButton.contains("appendPath"))
                    {
                        QPushButton* btn = projPtr->AddButton(oneButton["buttonName"].toString(), oneButton["appendPath"].toString());
                        connect(btn, &QPushButton::clicked, this, [=](){OnBtnClicked(i, j);});
                    }
                }
            }
        }
    }

    // Console
    _mainVerticalLayout->addWidget(ui->ConsoleText);
}

void
QuickOpenWindow::ClearOldItem()
{
    for (int i = 0; i > _uiItemVec.size(); i++)
    {
        auto layoutPtr = _uiItemVec[i]->GetOuterLayout();
        _mainVerticalLayout->removeItem(layoutPtr);

        delete _uiItemVec[i];
    }

    _uiItemVec.clear();
}

void
QuickOpenWindow::OnBtnClicked(int projIndex, int btnIndex)
{
    auto projItemPtr = _uiItemVec[projIndex];
    QString str = projItemPtr->GetBasePath();
    str += projItemPtr->GetIndexButtonString(btnIndex);
    ui->ConsoleText->setText("[Open Folder] path=" + str);
    QDesktopServices::openUrl(QUrl(str));
}
