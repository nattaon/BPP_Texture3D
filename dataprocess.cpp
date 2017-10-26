#include "dataprocess.h"

int binpacking(int total_box_to_pack,
	int bin_w, int bin_h, int bin_d,
	int *box_w, int *box_h, int *box_d,
	int *_box_x, int *_box_y, int *_box_z,
	int *_orien_x, int *_orien_y, int *_orien_z,
	int *_bin_no, int *_item_no);

DataProcess::DataProcess()
{

}

void DataProcess::NewPackingOBJElement(int number)
{
	//for (int i = 0; i < number;i++)
	for (int i = 0; i < number; i++)
		vpacking_obj.push_back(PACKING());

	//qDebug() << packing_obj.size();
}

void DataProcess::CalculateBPP(int total_boxes, int bin_w, int bin_h, int bin_d)
//vector<int>&width, vector<int>&height, vector<int>&depth)
{


	// new variable and get value from ui
	int *boxes_r = new int[total_boxes];
	int *boxes_g = new int[total_boxes];
	int *boxes_b = new int[total_boxes];

	int *boxes_x_orient = new int[total_boxes];
	int *boxes_y_orient = new int[total_boxes];
	int *boxes_z_orient = new int[total_boxes];

	int *boxes_x_pos = new int[total_boxes];
	int *boxes_y_pos = new int[total_boxes];
	int *boxes_z_pos = new int[total_boxes];

	int *boxes_x_dim = new int[total_boxes];
	int *boxes_y_dim = new int[total_boxes];
	int *boxes_z_dim = new int[total_boxes];

	int *boxes_bin_num = new int[total_boxes];
	int *boxes_item_num = new int[total_boxes];
	int *boxes_item_order = new int[total_boxes];

	int *boxes_item_rotation = new int[total_boxes];

	for (int i = 0; i < total_boxes; i++)
	{

		boxes_x_dim[i] = vpacking_obj[i].x_mm;
		boxes_y_dim[i] = vpacking_obj[i].y_mm;
		boxes_z_dim[i] = vpacking_obj[i].z_mm;

		boxes_x_pos[i] = 0;
		boxes_y_pos[i] = 0;
		boxes_z_pos[i] = 0;

		boxes_x_orient[i] = 0;
		boxes_y_orient[i] = 0;
		boxes_z_orient[i] = 0;


		boxes_bin_num[i] = 0;
		boxes_item_num[i] = i;
		boxes_item_rotation[i] = -1;

	}
	// call binpack_erhan_modify.cpp
	binpacking(total_boxes,
		bin_w, bin_h, bin_d,
		boxes_x_dim, boxes_y_dim, boxes_z_dim,
		boxes_x_pos, boxes_y_pos, boxes_z_pos,
		boxes_x_orient, boxes_y_orient, boxes_z_orient,
		boxes_bin_num, boxes_item_num);

	//CalculateRotationCase
	for (int i = 0; i < total_boxes; i++)
	{
		if (boxes_bin_num[i] != 1) // not pack in same bin no.1
		{
			boxes_item_rotation[i] = -1;
		}
		else if (boxes_x_dim[i] == boxes_x_orient[i] &&
			boxes_y_dim[i] == boxes_y_orient[i] &&
			boxes_z_dim[i] == boxes_z_orient[i])
		{
			boxes_item_rotation[i] = 0;
		}
		else if (boxes_x_dim[i] == boxes_x_orient[i] &&
			boxes_y_dim[i] == boxes_z_orient[i] &&
			boxes_z_dim[i] == boxes_y_orient[i])
		{
			boxes_item_rotation[i] = 1;
		}
		else if (boxes_x_dim[i] == boxes_y_orient[i] &&
			boxes_y_dim[i] == boxes_x_orient[i] &&
			boxes_z_dim[i] == boxes_z_orient[i])
		{
			boxes_item_rotation[i] = 2;
		}
		else if (boxes_x_dim[i] == boxes_y_orient[i] &&
			boxes_y_dim[i] == boxes_z_orient[i] &&
			boxes_z_dim[i] == boxes_x_orient[i])
		{
			boxes_item_rotation[i] = 3;
		}
		else if (boxes_x_dim[i] == boxes_z_orient[i] &&
			boxes_y_dim[i] == boxes_y_orient[i] &&
			boxes_z_dim[i] == boxes_x_orient[i])
		{
			boxes_item_rotation[i] = 4;
		}
		else if (boxes_x_dim[i] == boxes_z_orient[i] &&
			boxes_y_dim[i] == boxes_x_orient[i] &&
			boxes_z_dim[i] == boxes_y_orient[i])
		{
			boxes_item_rotation[i] = 5;
		}
	}


	//just print for debug
	for (int i = 0; i < total_boxes; i++)
	{
		vpacking_obj[i].box_id = boxes_item_num[i];
		vpacking_obj[i].x_mm = boxes_x_dim[i];
		vpacking_obj[i].y_mm = boxes_y_dim[i];
		vpacking_obj[i].z_mm = boxes_z_dim[i];
		vpacking_obj[i].pos_x_mm = boxes_x_pos[i];
		vpacking_obj[i].pos_y_mm = boxes_y_pos[i];
		vpacking_obj[i].pos_z_mm = boxes_z_pos[i];
		vpacking_obj[i].rot_id = boxes_item_rotation[i];


		vpacking_obj[i].x_dm = boxes_x_dim[i] * 0.01;
		vpacking_obj[i].y_dm = boxes_y_dim[i] * 0.01;
		vpacking_obj[i].z_dm = boxes_z_dim[i] * 0.01;
		vpacking_obj[i].pos_x_dm = boxes_x_pos[i] * 0.01;
		vpacking_obj[i].pos_y_dm = boxes_y_pos[i] * 0.01;
		vpacking_obj[i].pos_z_dm = boxes_z_pos[i] * 0.01;

	}
	for (int i = 0; i < total_boxes; i++)
	{
		cout
			<< "item_num." << vpacking_obj[i].box_id << ", "
			<< "whd:" << vpacking_obj[i].x_mm << "x" << vpacking_obj[i].y_mm << "x" << vpacking_obj[i].z_mm << ", "
			<< "pos:" << vpacking_obj[i].pos_x_mm << "," << vpacking_obj[i].pos_y_mm << "," << vpacking_obj[i].pos_z_mm << ", "
			<< "rotation:" << vpacking_obj[i].rot_id << ", "
			<< endl;
	}

	//sort
	//PACKING::sort_by = 'x';
	//std::sort(vpacking_obj.begin(), vpacking_obj.end());

	//std::sort(vpacking_obj.begin(), vpacking_obj.end(), packing_obj);  // OK

	//std::sort(vpacking_obj.begin(), vpacking_obj.end(), [](PACKING &a, PACKING &b){ return a.rot_id < b.rot_id; });

	//1.sort y : height min to max
	std::sort(vpacking_obj.begin(), vpacking_obj.begin() + 12, [](PACKING &a, PACKING &b){ return a.pos_y_mm < b.pos_y_mm; });

	cout << "sort y " << endl;
	for (int i = 0; i < total_boxes; i++)
	{
		cout << i << ":"
			<< "item_num." << vpacking_obj[i].box_id << ", "
			<< "whd:" << vpacking_obj[i].x_mm << "x" << vpacking_obj[i].y_mm << "x" << vpacking_obj[i].z_mm << ", "
			<< "pos:" << vpacking_obj[i].pos_x_mm << "," << vpacking_obj[i].pos_y_mm << "," << vpacking_obj[i].pos_z_mm << ", "
			<< "rotation:" << vpacking_obj[i].rot_id << ", "
			<< endl;
	}


	//find range
	int z_start_index = 0;
	int y_start_index = 0;
	int x_start_index = 0;
	//2. loop in y axis(height)
	for (int i = y_start_index; i<total_boxes - 1; i++)
	{

		//cout << "i=" << i << endl;
		//3. if next y item is different value
		// sort z(deep) inside each group of y
		if (vpacking_obj[i].pos_y_mm != vpacking_obj[i + 1].pos_y_mm)
		{
			cout << endl;
			cout << "i " << i << "!=" << i + 1 << endl;
			cout << "sort z: " << y_start_index << " to " << i + 1 << endl;
			std::sort(vpacking_obj.begin() + y_start_index, vpacking_obj.begin() + i + 1, [](PACKING &a, PACKING &b){ return a.pos_z_mm < b.pos_z_mm; });
			//printboxes_array();

			//4. in each group of same z(deep)
			// sort x(left to right)
			z_start_index = y_start_index;
			//cout << " z_start_index=" << z_start_index << endl;
			for (int j = z_start_index; j<i + 1; j++)
			{

				//cout << " j=" << j << endl;
				if (vpacking_obj[j].pos_z_mm != vpacking_obj[j + 1].pos_z_mm)
				{//////!!!!!!!TO  CHECK!!!!!!NO SORT X CORRECTLY AROUND THIS
					cout << "j " << j << "!=" << j + 1 << endl;
					cout << "sort x: " << z_start_index << " to " << j + 1 << endl;
					std::sort(vpacking_obj.begin() + z_start_index, vpacking_obj.begin() + j + 1, [](PACKING &a, PACKING &b){ return a.pos_x_mm < b.pos_x_mm; });
					//printboxes_array();

					z_start_index = j + 1;
				}
			}
			y_start_index = i + 1;
		}

	}


	cout << endl;
	for (int i = 0; i < total_boxes; i++)
	{
		cout << i << ":"
			<< "item_num." << vpacking_obj[i].box_id << ", "
			<< "whd:" << vpacking_obj[i].x_mm << "x" << vpacking_obj[i].y_mm << "x" << vpacking_obj[i].z_mm << ", "
			<< "pos:" << vpacking_obj[i].pos_x_mm << "," << vpacking_obj[i].pos_y_mm << "," << vpacking_obj[i].pos_z_mm << ", "
			<< "rotation:" << vpacking_obj[i].rot_id << ", "
			<< endl;
	}


}


