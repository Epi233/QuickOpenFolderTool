//
// Created by Hsing on 2022/5/25.
//

#ifndef QUICKOPENFOLDER_PROJECTITEM_H
#define QUICKOPENFOLDER_PROJECTITEM_H

#include <QLayout>
#include <QPushButton>
#include <QLineEdit>
#include <vector>

class ProjectItem
{
public:
    ProjectItem(QString name, QString path);
    ~ProjectItem();

private:
    QString _name;
    QString _basePath;
    QVBoxLayout* _outerLayout;
    QLineEdit* _nameLineEdit;
    QHBoxLayout* _buttonLayout;

    std::vector<QPushButton*> _buttons;
    std::vector<QString> _buttonPath;

public:
    QVBoxLayout* GetOuterLayout();
    const std::vector<QPushButton*>& GetButtons();
    QString GetBasePath();
    QString GetIndexButtonString(int index);

public:
    QPushButton* AddButton(const QString& buttonName, const QString& buttonPath);
};


#endif //QUICKOPENFOLDER_PROJECTITEM_H
