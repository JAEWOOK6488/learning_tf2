#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "geometry_msgs/TransformStamped.h"

geometry_msgs::PoseStamped msg;

void poseCallback(const geometry_msgs::PoseStamped::ConstPtr& m) {
    msg = *m;
    msg.header.stamp = ros::Time(0);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "tf_listener");
    ros::NodeHandle nh;

    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);

    ros::Subscriber poseSubscriber = nh.subscribe<geometry_msgs::PoseStamped>(
        "/pose_topic", 10, poseCallback);

    ros::Rate r(1);
    while (ros::ok()) {
        if (tfBuffer.canTransform("world", "home", ros::Time(0)) && !msg.header.frame_id.empty()) {
            try {
                geometry_msgs::TransformStamped transformStamped =
                    tfBuffer.lookupTransform("world", msg.header.frame_id, ros::Time(0));

                geometry_msgs::PoseStamped transformedPose;
                tf2::doTransform(msg, transformedPose, transformStamped);

                ROS_INFO_STREAM(transformedPose);
            } catch (tf2::TransformException& ex) {
                ROS_WARN("%s", ex.what());
            }
        } else {
            ROS_WARN("Cannot lookup transform between world and home");
        }

        ros::spinOnce();
        r.sleep();
    }

    return 0;
}
