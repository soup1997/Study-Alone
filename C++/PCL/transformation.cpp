// Transformation
// sensor frame --> body frame --> global(world) frame
// LiDAR 센서가 로봇 body 기준 x축으로 0.165m, z축으로 0.320m에 놓여져 있다고 하면 transformation은?

#include <iostream>
#include <pcl/common/transforms.h>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>


int main(int argc, char ** argv) {
    pcl::PointCloud<pcl::PointXYZ> cloud_src;

    pcl::PointXYZ point_xyz;

    for(int k = 0; k < 5; k++) {
        float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 5;
        float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 5;
        float z = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 5;

        point_xyz.x = x; point_xyz.y = y; point_xyz.z = z;
        cloud_src.push_back(point_xyz);
    }

    pcl::PointCloud<pcl::PointXYZ> pc_transformed;
    pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_transformed(new pcl::PointCloud<pcl::PointXYZ>); // shared_ptr

    Eigen::Matrix4f trans;
    trans << 1, 0, 0, 0.165,
             0, 1, 0, 0.000, 
             0, 0, 1, 0.320, 
             0, 0, 0, 1;
    
    pcl::transformPointCloud(cloud_src, *ptr_transformed, trans);
    pc_transformed = *ptr_transformed;

    return 0;
}