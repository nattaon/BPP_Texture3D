#include "viewerwindow.h"

ViewerWindow::ViewerWindow()
{
	window_view.reset(new pcl::visualization::PCLVisualizer("window_view"));
	window_view->setPosition(50, 0);//window position
	window_view->setBackgroundColor(0, 0, 0);
	window_view->initCameraParameters();
	window_view->setRepresentationToSurfaceForAllActors();
	//window_view->getRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera()->SetParallelProjection(1);
	//window_view->registerKeyboardCallback(ViewerWindow::keyboardEventOccurred, (void*)&window_view);
	window_view->registerKeyboardCallback(&ViewerWindow::keyboardEventOccurred, *this);
	SetCameraParameter();
}

void ViewerWindow::keyboardEventOccurred(const pcl::visualization::KeyboardEvent &event, void* junk)
{
	if (event.getKeySym() == "Right" && event.keyDown())
	{
		//cout << "Right down" << endl;
		if (current_index < total_boxes)
		{
			current_index++;
			//cout << current_index << endl;
			ShowObject(current_index);
		}

	}
	else if (event.getKeySym() == "Left" && event.keyDown())
	{
		//cout << "Left down" << endl;
		if (current_index > 1)
		{
			current_index--;
			//cout << current_index << endl;
			ShowObject(current_index);
		}
	}
	else if (event.getKeySym() == "s" && event.keyDown()) // r is set to default camera
	{
		SetCameraParameter();
	}

	//cout << event.getKeySym() << endl;
};

void ViewerWindow::InitialPacking(std::vector<PACKING> &vpack_obj, int bin_w, int bin_h, int bin_d)
{

	bin_width = bin_w*0.01;
	bin_height = bin_h*0.01;
	bin_depth = bin_d*0.01;

	cout << "ShowAllPacking" << endl;
	float theta = -M_PI / 2; // The angle of rotation in radians

	total_boxes = vpack_obj.size();

	for (int i = 0; i < total_boxes; ++i) {
		mesh_id.push_back(pcl::TextureMesh());
		pcl::io::loadOBJFile(vpack_obj[i].filename.toStdString(), mesh_id[i]);

		Eigen::Affine3f transform = Eigen::Affine3f::Identity();

		if (vpack_obj[i].rot_id == 0)
		{
			//move pivot point from center to corner
			transform.translation() <<
				vpack_obj[i].pos_x_dm + vpack_obj[i].x_dm / 2,
				vpack_obj[i].pos_y_dm + vpack_obj[i].y_dm / 2,
				vpack_obj[i].pos_z_dm + vpack_obj[i].z_dm / 2;

			mesh_id[i].cloud = TransformationPointCloud2(mesh_id[i].cloud, transform);
		}
		else if (vpack_obj[i].rot_id == 1)
		{
			transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitX()));
			transform.translation() <<
				vpack_obj[i].pos_x_dm + vpack_obj[i].x_dm / 2,
				vpack_obj[i].pos_y_dm + vpack_obj[i].z_dm / 2,
				vpack_obj[i].pos_z_dm + vpack_obj[i].y_dm / 2;

			mesh_id[i].cloud = TransformationPointCloud2(mesh_id[i].cloud, transform);

		}
		else if (vpack_obj[i].rot_id == 2)
		{
			transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
			transform.translation() <<
				vpack_obj[i].pos_x_dm + vpack_obj[i].y_dm / 2,
				vpack_obj[i].pos_y_dm + vpack_obj[i].x_dm / 2,
				vpack_obj[i].pos_z_dm + vpack_obj[i].z_dm / 2;

			mesh_id[i].cloud = TransformationPointCloud2(mesh_id[i].cloud, transform);
		}
		else if (vpack_obj[i].rot_id == 3)
		{
			transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitZ()));
			transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitY()));

			transform.translation() <<
				vpack_obj[i].pos_x_dm + vpack_obj[i].z_dm / 2,
				vpack_obj[i].pos_y_dm + vpack_obj[i].x_dm / 2,
				vpack_obj[i].pos_z_dm + vpack_obj[i].y_dm / 2;

			mesh_id[i].cloud = TransformationPointCloud2(mesh_id[i].cloud, transform);
		}
		else if (vpack_obj[i].rot_id == 4)
		{
			transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitY()));

			transform.translation() <<
				vpack_obj[i].pos_x_dm + vpack_obj[i].z_dm / 2,
				vpack_obj[i].pos_y_dm + vpack_obj[i].y_dm / 2,
				vpack_obj[i].pos_z_dm + vpack_obj[i].x_dm / 2;

			mesh_id[i].cloud = TransformationPointCloud2(mesh_id[i].cloud, transform);
		}
		else if (vpack_obj[i].rot_id == 5)
		{
			transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitX()));
			transform.rotate(Eigen::AngleAxisf(theta, Eigen::Vector3f::UnitY()));

			transform.translation() <<
				vpack_obj[i].pos_x_dm + vpack_obj[i].y_dm / 2,
				vpack_obj[i].pos_y_dm + vpack_obj[i].z_dm / 2,
				vpack_obj[i].pos_z_dm + vpack_obj[i].x_dm / 2;

			mesh_id[i].cloud = TransformationPointCloud2(mesh_id[i].cloud, transform);
		}




		//qDebug() << i << ":" << "rot-" << vpack_obj[i].rot_id << ":" << vpack_obj[i].pos_x_dm << "," << vpack_obj[i].pos_y_dm << "," << vpack_obj[i].pos_z_dm;

	}

	// red bin
	window_view->addCube(0, bin_width, 0, bin_height, 0, bin_depth, 1.0, 0, 0, "wireframe_bin", 0);
	window_view->addCoordinateSystem(3.0, "axis", 0);

	current_index = 1;
	ShowObject(current_index);
}



void ViewerWindow::ShowObject(int index)
{
	window_view->removeAllPointClouds();
	//window_view->removeAllShapes();

	// viewer.addCube(16.2, 18.2, -7.9, -5.9, 0.21, 2.21, 1.0, 0, 0, "cube", 0);
	//window_view->addCube(xmin, xmax, ymin, ymax, zmin, zmax, r, g, b, shapename);
	

	//cout << current_index << endl;
	//string t_name = "texture";
	//viewer->addTextureMesh(mesh_id[current_index-1], t_name, 0);

	for (int i = 0; i < index; i++)
	{
		string t_name = "texture";
		t_name = t_name + to_string(i);
		//cout << t_name << endl;

		window_view->addTextureMesh(mesh_id[i], t_name, 0);
	}

	
	//window_view->spin(); // use this; ui window disappear
	window_view->spinOnce(); // use this; ui window not disappear


}

pcl::PCLPointCloud2 ViewerWindow::TransformationPointCloud2(pcl::PCLPointCloud2 in, Eigen::Affine3f transform)
{
	pcl::PCLPointCloud2 pc2;
	pcl::PointCloud<pcl::PointXYZ> cloud, t_cloud;

	pcl::fromPCLPointCloud2(in, cloud);

	pcl::transformPointCloud(cloud, t_cloud, transform);

	pcl::PCLPointCloud2 out;
	pcl::toPCLPointCloud2(t_cloud, out);

	return out;

}

void ViewerWindow::SetCameraParameter()
{
	/*->setCameraPosition(
		pos_x, pos_y, pos_z,
		focal_x, focal_y, focal_z,
		up_x, up_y, up_z);*/
	window_view->setCameraPosition(
		1.7991, 3.85348, 5.33829,
		1.18377, -0.314565, 0.0934765,
		-0.106669, 0.78448, -0.610911);

	window_view->setCameraClipDistances(0.0103171, 10.3171);
	window_view->setCameraFieldOfView(0.8574994601);//radian
	window_view->spinOnce();



}