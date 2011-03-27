#include "mainwindow.h"

#include "apitracecall.h"
#include "apicalldelegate.h"
#include "apitracemodel.h"
#include "apitracefilter.h"

#include <QAction>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QWebView>


MainWindow::MainWindow()
    : QMainWindow()
{
    m_ui.setupUi(this);

    m_model = new ApiTraceModel();
    m_proxyModel = new ApiTraceFilter();
    m_proxyModel->setSourceModel(m_model);
    m_ui.callView->setModel(m_proxyModel);
    m_ui.callView->setItemDelegate(new ApiCallDelegate);
    for (int column = 0; column < m_model->columnCount(); ++column)
        m_ui.callView->resizeColumnToContents(column);

    m_ui.detailsDock->hide();

    connect(m_ui.actionOpen, SIGNAL(triggered()),
            this, SLOT(openTrace()));

    connect(m_ui.callView, SIGNAL(activated(const QModelIndex &)),
            this, SLOT(callItemSelected(const QModelIndex &)));
}

void MainWindow::openTrace()
{
    QString fileName =
        QFileDialog::getOpenFileName(
            this,
            tr("Open Trace"),
            QDir::homePath(),
            tr("Trace Files (*.trace)"));

    qDebug()<< "File name : " <<fileName;

    m_model->loadTraceFile(fileName);
}

void MainWindow::loadTrace(const QString &fileName)
{
    qDebug()<< "Loading  : " <<fileName;

    m_model->loadTraceFile(fileName);
}

void MainWindow::callItemSelected(const QModelIndex &index)
{
    ApiTraceCall *call = index.data().value<ApiTraceCall*>();
    if (call) {
        m_ui.detailsWebView->setHtml(call->richText());
        m_ui.detailsDock->show();
    } else {
        m_ui.detailsDock->hide();
    }
}

#include "mainwindow.moc"