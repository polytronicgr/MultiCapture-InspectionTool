#pragma once
#include <QPushButton>
#include <QTableWidget>
#include "ScannerInteraction.h"
#include "Lib/json.hpp"
#include "ProjectTableView.h"
#include <QErrorMessage>

QT_BEGIN_NAMESPACE
class QPushButton;
class QTableWidget;
class QTableView;
QT_END_NAMESPACE

class ProjectView : public QObject, public IDeviceResponder
{
	Q_OBJECT

public:
	ProjectView(QPushButton*, QPushButton*, QTableView*, ScannerInteraction*);
	~ProjectView();

	signals:
	void transferProject(const int);

	public slots:
	void refreshProjects();

	private slots:
	void createCustomMenu(const QPoint &pos);
	void changeProjectName();
	void removeProject();

	void triggerProjectChange();
	void scannerConnected();
	void respondToScanner(ScannerCommands, QByteArray) override;

private:
	const int timerDuration = 30000; //30sec

	ScannerInteraction* connector;
	ProjectTableView* dataModel;
	QMenu* nameChange;
	QModelIndex* contextMenuIndex;
	QErrorMessage* projectError;

	void processProjects(QByteArray) const;
	void setupContextMenu();
	void reportPossibleError(QByteArray) const;
	void currentProjectResult(QByteArray);

	//ui elements
	QPushButton* refresh, *transfer;
	QTableView* table;
};