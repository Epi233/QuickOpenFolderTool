//
// Created by Hsing on 2022/5/25.
//

#include <QOpenGLContext>
#include "ProjectItem.h"

ProjectItem::ProjectItem(QString name, QString basePath)
{
    _name = name;
    _basePath = basePath;

    _outerLayout = new QVBoxLayout();

    _nameLineEdit = new QLineEdit();
    _nameLineEdit->setReadOnly(true);
    _nameLineEdit->setText(_name);

    _outerLayout->addWidget(_nameLineEdit);

    _buttonLayout = new QHBoxLayout();
    _outerLayout->addLayout(_buttonLayout);
}

ProjectItem::~ProjectItem()
{
    for (int i = 0; i < _buttons.size(); i++)
    {
        _buttonLayout->removeWidget(_buttons[i]);
        delete _buttons[i];
    }

    _buttons.clear();

    _outerLayout->removeItem(_buttonLayout);
    delete _buttonLayout;

    _outerLayout->removeWidget(_nameLineEdit);
    delete _nameLineEdit;

    delete _outerLayout;
}

QPushButton*
ProjectItem::AddButton(const QString& buttonName, const QString& buttonPath)
{
    QPushButton* btn = new QPushButton();
    btn->setText(buttonName);

    _buttonLayout->addWidget(btn);

    _buttons.push_back(btn);
    _buttonPath.push_back(buttonPath);

    return btn;
}

QVBoxLayout*
ProjectItem::GetOuterLayout()
{
    return _outerLayout;
}

QString
ProjectItem::GetBasePath()
{
    return _basePath;
}

QString
ProjectItem::GetIndexButtonString(int index)
{
    if (index < 0 || index >= _buttonPath.size())
        return "";

    return _buttonPath[index];
}

const std::vector<QPushButton*>&
ProjectItem::GetButtons()
{
    return _buttons;
}
