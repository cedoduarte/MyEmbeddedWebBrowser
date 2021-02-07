#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MyTcpServer;
class MyEmbeddedWidget;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
private slots:
    void onReadyRead(const QString &message);
    void on_actionSalir_triggered();

    void on_actionDuarteCorporation_Tutoriales_triggered();

    void on_actionGoogle_triggered();

    void on_actionFacebook_triggered();

    void on_actionInstagram_triggered();

    void on_actionYoutube_triggered();

    void on_actionTwitter_triggered();

    void on_actionindex_html_triggered();

private:
    int getPort() const;
    MyEmbeddedWidget *makeWebBrowser();

    Ui::MainWindow *ui;
    MyTcpServer *m_server;
    MyEmbeddedWidget *m_webBrowser;
};

#endif // MAINWINDOW_H
