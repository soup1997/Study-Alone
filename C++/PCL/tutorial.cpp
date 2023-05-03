#include <iostream>
#include <pcl/point_types.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/conversions.h>


template <typename T>
void print_pc(pcl::PointCloud<T> & cloud) {
    int cnt = 0;
    for(const auto& pt: cloud.points) {
        std::cout << cnt++ << ": ";
        std::cout << pt.x << ", " << pt.y << ", " << pt.z << std::endl;
    }
}

template <typename T>
void iterator_func(pcl::PointCloud<T> & cloud) {
    // begin(): PointCloud의 첫 부분을 가리키는 iterator를 반환
    std::cout << "begin(): ";
    std::cout << cloud.begin()->x << ", ";
    std::cout << cloud.begin()->y << ", ";
    std::cout << cloud.begin()->z << std::endl;
    std::cout << "---------------------" << std::endl;

    // end(): PointCloud의 끝 부분을 가리키는 iterator를 반환
    std::cout << "end(): ";
    std::cout << (cloud.end()-1)->x << ", ";
    std::cout << (cloud.end()-1)->y << ", ";
    std::cout << (cloud.end()-1)->z << std::endl;
    std::cout << "---------------------" << std::endl;

    // front(): 첫번째 원소를 반환
    std::cout << "front(): ";
    std::cout << cloud.front().x << ", ";
    std::cout << cloud.front().y << ", ";
    std::cout << cloud.front().z << std::endl;
    std::cout << "---------------------" << std::endl;

    // back(): 마지막 원소를 반환
    std::cout << "back(): ";
    std::cout << cloud.back().x << ", ";
    std::cout << cloud.back().y << ", ";
    std::cout << cloud.back().z << std::endl;
    std::cout << "---------------------" << std::endl;

    // at(index): index에 해당하는 요소를 반환
    std::cout << "at(1): ";
    std::cout << cloud.at(1).x << ", ";
    std::cout << cloud.at(1).y << ", ";
    std::cout << cloud.at(1).z << std::endl;
    std::cout << "---------------------" << std::endl;
}

template <typename T>
void other_func(pcl::PointCloud<T>& cloud) {
    // empty(): PointCloud가 비어있는지 확인
    if (cloud.empty()) {
        std::cout << "True";
    } else std::cout << "False";

    std::cout << "| size of pc: " << cloud.size() << std::endl;
    std::cout << "---------------------" << std::endl;

    // clear(): PointCloud를 clear
    cloud.clear();
    if(cloud.empty()) {
        std::cout << "True";
    } else std::cout << "False";

    std::cout << "| size of pc: " << cloud.size() << std::endl;
}


int main(int argc, char** argv) {
    pcl::PointCloud<pcl::PointXYZ> cloud_init0;
    cloud_init0.resize(3); // cloud의 size를 3으로 설정

    cloud_init0.points[0].x = 1; cloud_init0.points[0].y = 2; cloud_init0[0].z = 3;
    cloud_init0.points[1].x = 4; cloud_init0.points[1].y = 5; cloud_init0[1].z = 6;
    cloud_init0.points[2].x = 7; cloud_init0.points[2].y = 8; cloud_init0[2].z = 9;

    std::cout << "cloud_init0: " << std::endl;
    print_pc(cloud_init0);
    std::cout << "---------------------" << std::endl;
    

    pcl::PointCloud<pcl::PointXYZ> cloud_init1;
    pcl::PointXYZ point_xyz; // pcl::PointXYZ이라는 type에 데이터를 담는다.
    
    point_xyz.x = 1; point_xyz.y = 2; point_xyz.z = 3;
    cloud_init1.push_back(point_xyz); // std::vector처럼 push_back 가능

    point_xyz.x = 4; point_xyz.y = 5; point_xyz.z = 6;
    cloud_init1.push_back(point_xyz);

    point_xyz.x = 7; point_xyz.y = 8; point_xyz.z = 9;
    cloud_init1.push_back(point_xyz);

    std::cout << "cloud_init1:  "<< std::endl;
    print_pc(cloud_init1);
    std::cout << "---------------------" << std::endl;


    pcl::PointCloud<pcl::PointXYZ> cloud2;
    cloud2.push_back(pcl::PointXYZ(1, 2, 3));
    cloud2.push_back(pcl::PointXYZ(4, 5, 6));

    pcl::PointCloud<pcl::PointXYZ> cloud3;
    cloud3.push_back(pcl::PointXYZ(7, 8, 9));
    cloud3.push_back(pcl::PointXYZ(10, 11, 12));

    cloud2 += cloud3; // push_back과 동일한 기능, pointcloud 사이의 덧셈 연산이 아님!

    std::cout << "size: " << cloud2.size() << std::endl; // size(): cloud안에 몇개의 포인트가 존재하는지 return 
    print_pc(cloud2);

    cloud3.push_back(pcl::PointXYZ(12, 13, 14));
    std::cout << "After: " << std::endl;
    print_pc(cloud3);

    iterator_func(cloud3);
    other_func(cloud3);
}
