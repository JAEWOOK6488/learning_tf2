#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "geometry_msgs/TransformStamped.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "tf_listener");
    ros::NodeHandle nh;

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);

    ros::Rate rate(1.0);

    while (ros::ok()) {
        try {
            geometry_msgs::TransformStamped transformStamped;

            // 변환 정보 수신
            // target_frame, source_frame, time
            transformStamped = tfBuffer.lookupTransform("world", "home", ros::Time(0));

            // 변환 정보 출력
            ROS_INFO("Received Transform - Translation: [%.2f, %.2f, %.2f], Rotation: [%.2f, %.2f, %.2f, %.2f]",
                     transformStamped.transform.translation.x,
                     transformStamped.transform.translation.y,
                     transformStamped.transform.translation.z,
                     transformStamped.transform.rotation.x,
                     transformStamped.transform.rotation.y,
                     transformStamped.transform.rotation.z,
                     transformStamped.transform.rotation.w);            
        }
        catch (tf2::TransformException& ex) {
            ROS_WARN("%s", ex.what());
        }

        rate.sleep();
    }

    return 0;
}