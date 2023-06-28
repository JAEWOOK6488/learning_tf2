#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include <random>
#include "tf2/LinearMath/Quaternion.h"
#include "tf2/LinearMath/Matrix3x3.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pose_pub");
    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<geometry_msgs::PoseStamped>("pose_topic", 10);
    ros::Rate rate(1);
    
    while (ros::ok())
    {
        geometry_msgs::PoseStamped msg;

        msg.header.stamp = ros::Time::now();
        msg.header.frame_id = "home";

        msg.pose.position.x = -5;
        msg.pose.position.y = 10;
        msg.pose.position.z = 0;

        // tf2::Quaternion q;
        // q.setRPY(roll, pitch, yaw);

        msg.pose.orientation.w = 1;

        pub.publish(msg);

        rate.sleep();
    }
    return 0;
}