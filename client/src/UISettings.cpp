//
// Created by glithaud on 9/27/19.
//

#include <QCoreApplication>
#include <QSettings>
#include <QApplication>
#include "../includes/UISettings.hpp"
#include "../includes/mainWindow.hpp"
#include <QStandardPaths>
#include <QFile>

class QSettings;
class QFile;

UISettings::UISettings(QWidget *parent) {
    path = new QString(QApplication::applicationDirPath() + "/demosettings.ini");
    if (QFile(path[0]).exists()) {
       return;
    } else {
        createSettings();
    }
}

void UISettings::createSettings()
{
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.beginGroup("MainWindow");

    settings_.setValue("width", 5);
    settings_.setValue("height", 5);
    settings_.setValue("color", "#F7F7F7");
    settings_.setValue("font", "");
    settings_.setValue("fontSize", 15);
    settings_.setValue("colorLabel", "#F7F7F7");

    settings_.endGroup();

    settings_.beginGroup("Button");

    settings_.setValue("send", "#1E8E98");
    settings_.setValue("call", "#DC143C");
    settings_.setValue("add", "#E79C0F");

    settings_.endGroup();

    settings_.beginGroup("ImgBackground");

    settings_.setValue("active", 1);
    settings_.setValue("message", "");
    settings_.setValue("contact", "");
    settings_.setValue("text", "");

    settings_.endGroup();
}

QString UISettings::getMainWindow() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString color = settings_.value("MainWindow/color").toString();
    QString font = settings_.value("MainWindow/font").toString();
    int fontsize = settings_.value("MainWindow/fontSize").toInt();
    return QString("background-color: %1; font-size: %2px;").arg(color).arg(fontsize);
}

QString UISettings::getBackgroundColor() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString color = settings_.value("MainWindow/color").toString();
    return color;
}

int UISettings::getFontSize() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    int size = settings_.value("MainWindow/fontSize").toInt();
    return size;
}

int UISettings::getWidth() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    int width = settings_.value("MainWindow/width").toInt();
    return width;
}

int UISettings::getHeight() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    int height = settings_.value("MainWindow/height").toInt();
    return height;
}

QString UISettings::getLabel() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString color = settings_.value("MainWindow/color").toString();
    int fontsize = settings_.value("MainWindow/fontSize").toInt();
    return QString("background-color: %1 ; font-weight: bold; font-size: %2px;").arg(color).arg(fontsize + 10);
}

QString UISettings::getButtonCall() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString color = settings_.value("Button/call").toString();
    return QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color);
}

QString UISettings::getButtonSend() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString color = settings_.value("Button/send").toString();
    return QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color);
}

QString UISettings::getButtonAdd() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString color = settings_.value("Button/add").toString();
    return QString("background-color: %1;border: 1px solid black; border-radius: 10px; height: 40px; color: white; font-weight: bold;").arg(color);
}

int UISettings::getActiveImage() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    int active = settings_.value("ImgBackground/active").toInt();
    return active;
}

//Img back of list message box
QString UISettings::getMessage() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString path = settings_.value("ImgBackground/message").toString();

    if (path == "" || getActiveImage() == 0)
        return "background-color: rgb(255, 255, 255); border: 1px solid black; border-radius: 7px;";
    else {
        return QString("border-image: url(%1) 0 0 0 0 stretch stretch; border: 1px solid black; border-radius: 7px;").arg(path);
    }
}

//Img back of list contact box
QString UISettings::getContact() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString path = settings_.value("ImgBackground/contact").toString();
    if (path == "" || getActiveImage() == 0)
        return "background-color: rgb(255, 255, 255); border: 1px solid black; border-radius: 7px";
    else
        return QString("border-image: url(%1) 0 0 0 0 stretch stretch; position: auto; border: 1px solid black; border-radius: 7px; font-size: 20px").arg(path);
}

//Img back of text box
QString UISettings::getText() const {
    QSettings settings_(path[0], QSettings::NativeFormat);
    QString path = settings_.value("ImgBackground/text").toString();
    if (path == "" || getActiveImage() == 0)
        return "background-color: rgb(255, 255, 255); border: 1px solid black; border-radius: 7px";
    else
        return QString("border-image: url(%1) 0 0 0 0 stretch stretch; border: 1px solid black; border-radius: 7px; font-size: 20px").arg(path);
}

void UISettings::setMainColor(QString color) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("MainWindow/color", color);
}

void UISettings::setFont(QString font) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("MainWindow/font", font);
}

void UISettings::setSize(int size) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("MainWindow/fontSize", size);
}

void UISettings::setHeight(int height) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("MainWindow/height", height);
}

void UISettings::setWidth(int width) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("MainWindow/width", width);
}

void UISettings::setButtonSend(QString color) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("Button/send", color);
}

void UISettings::setButtonCall(QString color) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("Button/call", color);
}

void UISettings::setButtonAdd(QString color) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("Button/add", color);
}

void UISettings::setActiveImage(int value) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("ImgBackground/active", value);
}

void UISettings::setMessage(QString url) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("ImgBackground/message", url);
}

void UISettings::setContact(QString url) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("ImgBackground/contact", url);
}

void UISettings::setText(QString url) {
    QSettings settings_(path[0], QSettings::NativeFormat);
    settings_.setValue("ImgBackground/text", url);
}

UISettings::~UISettings()
{
}