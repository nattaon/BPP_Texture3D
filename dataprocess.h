#ifndef DATAPROCESS_H
#define DATAPROCESS_H

#include "SharedHeader.h"
#include <algorithm> //sort

using namespace std;


static struct PACKING {
	QString filename;
	int box_id;
	int x_mm, y_mm, z_mm;
	double x_dm, y_dm, z_dm;
	double pos_x_mm, pos_y_mm, pos_z_mm;
	double pos_x_dm, pos_y_dm, pos_z_dm;
	int rot_id;
	int order;
}packing_obj;

class DataProcess
{
public:
    DataProcess();
	void NewPackingOBJElement(int number);
	void CalculateBPP(int total_boxes, int bin_w, int bin_h, int bin_d);


	vector<PACKING> vpacking_obj;//12 obj

};

#endif // DATAPROCESS_H