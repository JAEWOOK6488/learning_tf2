#include "ros/ros.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf_home");
    ros::NodeHandle nh;

    tf2_ros::TransformBroadcaster broadcaster;

    ros::Rate rate(10.0);

    while (ros::ok())
    {
        geometry_msgs::TransformStamped transformStamped;

        // 변환 정보 설정
        transformStamped.header.stamp = ros::Time::now();
        transformStamped.header.frame_id = "world";
        transformStamped.child_frame_id = "home";

        transformStamped.transform.translation.x = 10.0;
        transformStamped.transform.translation.y = 10.0;
        transformStamped.transform.translation.z = 0.0;

        transformStamped.transform.rotation.x = 0.0;
        transformStamped.transform.rotation.y = 0.0;
        transformStamped.transform.rotation.z = 0.0;
        transformStamped.transform.rotation.w = 1.0;

        broadcaster.sendTransform(transformStamped);

        rate.sleep();
    }


    return 0;
}