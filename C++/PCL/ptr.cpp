#include <pcl/point_types.h>
#include <pcl/conversions.h>

using namespace std;

template <typename T>
void print_pc(pcl::PointCloud<T> & cloud) {
    int cnt = 0;
    for(const auto &pt: cloud.points) {
        cout << cnt++ << ": ";
        cout << pt.x << ", " << pt.y << ", " << pt.z << endl;
    }
}

template <typename T>
void print_pc_via_copy(pcl::PointCloud<T> cloud) {
    int cnt = 0;
    for (const auto &pt: cloud.points) {
        cout << cnt++ << ": ";
        cout << pt.x << ", " << pt.y << ", " << pt.z << endl;
    }
}

// pcl::PointCloud::Ptr == shared_ptr
void print_ptr(pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud) {
    int cnt = 0;
    for(const auto & pt: ptr_cloud->points) {
        cout << cnt++ << ": ";
        cout << pt.x << ", " << pt.y << ", " << pt.z << endl;
    }
}

void print_address(pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud) {
    cout << ptr_cloud << endl;
}

void print_address2(pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud) {
    cout << ptr_cloud << endl;
}

void add_pc(pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud) {
    ptr_cloud->points.emplace_back(pcl::PointXYZ(0, 0, 1));
}

void add_pc2(pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud) {
    ptr_cloud->points.emplace_back(pcl::PointXYZ(1, 0, 0));
}

void constptr_test(pcl::PointCloud<pcl::PointXYZ>::ConstPtr ptr_cloud) {
    pcl::PointCloud<pcl::PointXYZ> pc = *ptr_cloud;
    print_pc(pc);
    // print_pc(*ptr_cloud); // call by reference로 인한 에러 발생
    print_pc_via_copy(*ptr_cloud);
}

int main(int argc, char** argv) {
    pcl::PointCloud<pcl::PointXYZ> cloud2;
    cloud2.push_back(pcl::PointXYZ(1, 2, 3));
    cloud2.push_back(pcl::PointXYZ(4, 5, 6));

    pcl::PointCloud<pcl::PointXYZ> cloud3;
    cloud3.push_back(pcl::PointXYZ(7, 8, 9));
    cloud3.push_back(pcl::PointXYZ(10, 11, 12));

    cloud2 += cloud3;

    pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr ptr_cloud2(new pcl::PointCloud<pcl::PointXYZ>);
    
    // shared_ptr가 가리키는 객체에 데이터를 "복사"하겠다는 의미
    *ptr_cloud = cloud2;

    cout << "Before: " << endl;
    print_pc(cloud3);
    // 0: 7, 8, 9
    // 1: 10, 11, 12

    // ptr_cloud가 가리키고 있던 pointcloud를 cloud3에 복사해서 전달
    cloud3 = *ptr_cloud;
    cout << "After: "<< endl;
    print_pc(cloud3);
    // 0: 1, 2, 3
    // 1: 4, 5, 6
    // 2: 7, 8, 9
    // 3: 10, 11, 12

    // ptr간의 = 기호는 주소값을 공유한다는 의미, 같은 데이터를 가리킨다.
    ptr_cloud2 = ptr_cloud;
    cout << ptr_cloud << endl; // 서로 동일한 주소를 가리킴
    cout << ptr_cloud2 << endl; // 서로 동일한 주소를 가리킴

    // 따라서 print된 것을 확인해보면, ptr_cloud2 뒤에 넣었는데 ptr_cloud의 제일 뒤에도 (-1, -2, -3)이 들어가 있음!
    ptr_cloud2->points.emplace_back(pcl::PointXYZ(-1, -2, -3));
    cout << ptr_cloud2->points.back().x << ", " << ptr_cloud2->points.back().y << ", " << ptr_cloud2->points.back().z << endl;
}