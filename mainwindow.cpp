#include "mainwindow.h"
#include "build/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	dataprocess = new DataProcess();
	viewerwindow = new ViewerWindow();
	
	total_boxes = 12;
	

	ManualAddOBJFile();// Add filename and dimension to dataprocess->vpacking_obj
	dataprocess->CalculateBPP(total_boxes, 320, 115, 250);// Packing result save in dataprocess->vpacking_obj
	UpdatePackingResultToTreeWidget();
	viewerwindow->InitialPacking(dataprocess->vpacking_obj, 320, 115, 250);

}


void MainWindow::ManualAddOBJFile()
{
	ui->treeWidget->header()->resizeSection(13, 500);


	obj_filename.push_back("../obj2/obj_711cookies.obj");	width.push_back(160);	height.push_back(95);	depth.push_back(60);
	obj_filename.push_back("../obj2/obj_alfort.obj");		width.push_back(170);	height.push_back(77);	depth.push_back(15);
	obj_filename.push_back("../obj2/obj_chocochips.obj");	width.push_back(157);	height.push_back(95);	depth.push_back(60);
	obj_filename.push_back("../obj2/obj_chocolasenu.obj");	width.push_back(159);	height.push_back(96);	depth.push_back(63);
	obj_filename.push_back("../obj2/obj_collon.obj");		width.push_back(158);	height.push_back(98);	depth.push_back(63);
	obj_filename.push_back("../obj2/obj_flan.obj");			width.push_back(163);	height.push_back(90);	depth.push_back(25);
	obj_filename.push_back("../obj2/obj_hokkaido-choc.obj"); width.push_back(230);	height.push_back(114);	depth.push_back(37);
	obj_filename.push_back("../obj2/obj_kinoyama.obj");		width.push_back(150);	height.push_back(89);	depth.push_back(30);
	obj_filename.push_back("../obj2/obj_meltykiss.obj");	width.push_back(111);	height.push_back(111);	depth.push_back(52);
	obj_filename.push_back("../obj2/obj_milky.obj");		width.push_back(116);	height.push_back(95);	depth.push_back(35);
	obj_filename.push_back("../obj2/obj_shriver.obj");		width.push_back(203);	height.push_back(97);	depth.push_back(53);
	obj_filename.push_back("../obj2/obj_teddy.obj");		width.push_back(106);	height.push_back(84);	depth.push_back(35);

	//qDebug() << obj_filename[0];
	//qDebug() << obj_filename.size();

	dataprocess->NewPackingOBJElement(obj_filename.size());
	//qDebug() << dataprocess->packing_obj.size();


	for (int i = 0; i < obj_filename.size(); i++)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);
		item->setText(13, obj_filename[i]);
		item->setText(1, QString::number(width[i]));
		item->setText(2, QString::number(height[i]));
		item->setText(3, QString::number(depth[i]));
		ui->treeWidget->addTopLevelItem(item);


		//packing_obj.push_back(packing_obj_struct());
		dataprocess->vpacking_obj[i].filename = obj_filename[i];
		dataprocess->vpacking_obj[i].x_mm = width[i];
		dataprocess->vpacking_obj[i].y_mm = height[i];
		dataprocess->vpacking_obj[i].z_mm = depth[i];

	}


}

void MainWindow::UpdatePackingResultToTreeWidget()
{
	for (int i = 0; i < total_boxes; i++)
	{
		QTreeWidgetItem *item = ui->treeWidget->topLevelItem(i);

		item->setText(0, QString::number(dataprocess->vpacking_obj[i].box_id));

		item->setText(5, QString::number(dataprocess->vpacking_obj[i].pos_x_mm));
		item->setText(6, QString::number(dataprocess->vpacking_obj[i].pos_y_mm));
		item->setText(7, QString::number(dataprocess->vpacking_obj[i].pos_z_mm));

		item->setText(11, QString::number(dataprocess->vpacking_obj[i].rot_id));
		//item->setText(12, QString::number(dataprocess->vpacking_obj[i].order));
	}
}

MainWindow::~MainWindow()
{
    delete ui;
}
