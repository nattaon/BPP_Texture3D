#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include "SharedHeader.h"
#include "DataProcess.h"

class ViewerWindow
{
public:
    ViewerWindow();
	boost::shared_ptr<pcl::visualization::PCLVisualizer> window_view;
	void keyboardEventOccurred(const pcl::visualization::KeyboardEvent &event, void* junk);


	void InitialPacking(std::vector<PACKING> &vpack_obj, int bin_w, int bin_h, int bin_d);
	void ShowObject(int index);
	void SetCameraParameter();

	int total_boxes;
	int current_index;//number of item to show



private:
	vector<pcl::TextureMesh> mesh_id;
	pcl::PCLPointCloud2 TransformationPointCloud2(pcl::PCLPointCloud2 in, Eigen::Affine3f transform);
	
	double bin_width,bin_height,bin_depth;


};

#endif // VIEWERWINDOW_H