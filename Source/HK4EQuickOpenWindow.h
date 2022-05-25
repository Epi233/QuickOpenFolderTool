//
// Created by Hsing on 2022/5/25.
//

#ifndef QUICKOPENFOLDER_HK4EQUICKOPENWINDOW_H
#define QUICKOPENFOLDER_HK4EQUICKOPENWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <vector>
#include <QLineEdit>
#include "ProjectItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class HK4EQuickOpenWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit HK4EQuickOpenWindow(QWidget *parent = nullptr);

    ~HK4EQuickOpenWindow() override;

private:
    Ui::MainWindow *ui;

    void SetStyle();

private: //Json
    void LoadJson();

private: // UI
    QVBoxLayout* _mainVerticalLayout;

    std::vector<ProjectItem*> _uiItemVec;

    void ClearOldItem();
    void OnBtnClicked(int projIndex, int btnIndex);
};


#endif //QUICKOPENFOLDER_HK4EQUICKOPENWINDOW_H
