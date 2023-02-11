#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTime>

class MyClient : public QWidget
{
    Q_OBJECT

private:

    QTcpSocket* m_pTcpSocket;
    QTextEdit*  m_ptxtInfo;
    QLineEdit*  m_ptxtInput;
    quint16     m_nNextBlockSize;

public:

    MyClient(const QString& strHost, const int nPort,QWidget *parent = nullptr);

private slots:

    void SReadyRead   (                                );
    void SError       (QAbstractSocket::SocketError err);
    void SSendToServer(                                );
    void SConnected   (                                );

};
#endif // MYCLIENT_H
