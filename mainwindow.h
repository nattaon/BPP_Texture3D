#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "SharedHeader.h"
#include "DataProcess.h"
#include "ViewerWindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	int total_boxes;//12 obj
	

private:
    Ui::MainWindow *ui;
	DataProcess *dataprocess;
	ViewerWindow *viewerwindow;

	std::vector<QString> obj_filename;//12 obj
	std::vector<int> width;//12 obj
	std::vector<int> height;//12 obj
	std::vector<int> depth;//12 obj

	void ManualAddOBJFile();
	void UpdatePackingResultToTreeWidget();



};

#endif // MAINWINDOW_H
