#include "myclient.h"

MyClient::MyClient(const QString& strHost, const int nPort,QWidget *parent) : QWidget(parent)
                                                                        , m_nNextBlockSize(0)
{

    m_pTcpSocket = new QTcpSocket(this);

    m_pTcpSocket->connectToHost(strHost,nPort);
    connect(m_pTcpSocket,SIGNAL(connected()),SLOT(SConnected()));
    connect(m_pTcpSocket,SIGNAL(readyRead()),SLOT(SReadyRead()));
    connect(m_pTcpSocket,SIGNAL(error(QAbstractSocket::SockedError)),this,SLOT(QAbstractSocket::SockedError));

    m_ptxtInfo  = new QTextEdit;
    m_ptxtInput = new QLineEdit;

    m_ptxtInfo->setReadOnly(true);

    QPushButton* pcmd = new QPushButton;
    connect(pcmd,SIGNAL(clicked()),SLOT(SSendToServer()));
    connect(m_ptxtInfo,SIGNAL(returnPresed()),this,SLOT(SSendToServer()));

    //Layout setup
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(new QLabel("<H1>Client</H1>"));
    pvbxLayout->addWidget(m_ptxtInfo);
    pvbxLayout->addWidget(m_ptxtInput);
    pvbxLayout->addWidget(pcmd);

    setLayout(pvbxLayout);

}

void MyClient::SReadyRead()
{
    QDataStream in(m_pTcpSocket);

    in.setVersion(QDataStream::Qt_5_3);

    for (; ; )
    {
        if(!m_nNextBlockSize)
        {
            if(m_pTcpSocket->bytesAvailable() < sizeof (quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if(m_pTcpSocket->bytesAvailable() < m_nNextBlockSize)
        {
            QTime time;
            QString str;

            in >> time >> str;

            m_ptxtInfo->append(time.toString() + " " + str);
            m_nNextBlockSize = 0;
        }
    }
}

void MyClient::SError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                    "The host was not found." :
                                    err == QAbstractSocket::RemoteHostClosedError ?
                                    "The remote host is closed.":
                                    err == QAbstractSocket::ConnectionRefusedError ?
                                    "The connection was refused." :
                                    QString(m_pTcpSocket->errorString())
                                   );
    m_ptxtInfo->append(strError);
}

void MyClient::SSendToServer()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_2);
    out << quint16(0) << QTime::currentTime() << m_ptxtInfo->toPlainText();

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof (quint16));

    m_pTcpSocket->write(arrBlock);
    m_ptxtInfo->setText("");
}

void MyClient::SConnected()
{
    m_ptxtInfo->append("Recived the connected() signal");
}

