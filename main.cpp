#include <QApplication>
#include "./view/mainwindow.hpp"
int main(int argc,char* argv[]){
    MainWindow *wnd;
    QApplication app(argc,argv);
    wnd=new MainWindow();
    wnd->show();
    return app.exec();
}
