#include "rclcpp/rclcpp.hpp"


int main (int argc, char** argv){
    // Initialize ROS2 communication
    rclcpp::init(argc, argv);
    
    // Create a node with shared pointer which will automatically handle deletes and new
    auto node = std::make_shared<rclcpp::Node>("cpp_test");

    // Have node print something
    RCLCPP_INFO(node->get_logger(), "Hello Cpp Node");

    // Spin pauses the program and keeps the node alive until you exit out
    rclcpp::spin(node);

    // Shuts off ROS2 communication
    rclcpp::shutdown();
    return 0;
}