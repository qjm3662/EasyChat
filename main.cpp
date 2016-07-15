#include <QtGui/QApplication>
#include "login.h"
#include <QDebug>
#include <QPainter>
#include <QPixmap>
#include <QTextCodec>
#include "ChatView.h"
#include "connext.h"
#include "FriendListItem.h"
#include <QListWidget>
#include "MainUI/MainUI.h"
#include "MainUI/mainitem.h"
#include "MainUI/GroupChat.h"
#include "client/client.h"
#include "client/clientstic.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //解决中文编码问题
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

//    MainWindow w;
//    w.show();
    //painter.drawLine(0,0,100,100);

//    Login l;

//    l.show();

//    ChatView cv;
//    cv.show();

//      GroupChat m;
//      m.show();
    connext c;
    c.show();

//    MainUI m;
//    m.show();

//    FriendListItem item;
//    item.show();

    int result = a.exec();
    //通知服务器已下线
    ClientStic::getInstance()->sendMessage("4", "00", "00", "00", "00");
    return result;
}
