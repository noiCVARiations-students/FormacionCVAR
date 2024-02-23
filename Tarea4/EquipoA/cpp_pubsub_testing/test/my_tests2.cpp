#include <gtest/gtest.h>
#include <vector>
#include "nodes/output.hpp"
#include "nodes/publisher.hpp"
#include "nodes/subscriber_member_function.hpp"
#include <thread>
#include <iostream>
#include "stdio.h"

TEST(testpool2, testtwo){
    rclcpp::init(0, nullptr);

    std::ifstream file("samples2.in");
    ASSERT_TRUE(file.is_open());

    std::vector<double> my_input = readDouble(file), my_output;
    my_output.reserve(16);

    auto subs = std::make_shared<MinimalSubscriber>(2);
    auto pub = std::make_shared<MinimalPublisher>(my_input);
    auto out = std::make_shared<MinimalOutput>(&my_output);

    std::thread minimalsubs([&](){
        rclcpp::spin(subs);
    });
    std::thread minimalout([&](){
        rclcpp::spin(out);
    });

    std::this_thread::sleep_for(2000ms);

    std::thread minimalpub([&](){
        rclcpp::spin(pub);
    });

    std::this_thread::sleep_for(10000ms);

    rclcpp::shutdown();
    minimalsubs.join();
    minimalout.join();
    minimalpub.join();

    std::ifstream ofile("samples2.out");
    ASSERT_GT(my_output.size(), 0);
    std::cout << "VECTOR SIZE IS: " << my_output.size() << std::endl;
    ASSERT_TRUE(ofile.is_open());
    double value;
    int i;
    for (i=0; !ofile.eof() && i < (int)my_output.size(); i++)
    {
        ofile >> value;
        std::cout << "the value is: " << value << " and the vector value is: " << my_output[i] << std::endl;
        ASSERT_FLOAT_EQ(value, my_output[i]);
    }
}

TEST(testpool3, testthree){
    rclcpp::init(0, nullptr);

    std::ifstream file("samples2.in");
    ASSERT_TRUE(file.is_open());

    std::vector<double> my_input = readDouble(file), my_output;
    my_output.reserve(16);

    auto subs = std::make_shared<MinimalSubscriber>(3);
    auto pub = std::make_shared<MinimalPublisher>(my_input);
    auto out = std::make_shared<MinimalOutput>(&my_output);

    std::thread minimalsubs([&](){
        rclcpp::spin(subs);
    });
    std::thread minimalout([&](){
        rclcpp::spin(out);
    });

    std::this_thread::sleep_for(2000ms);

    std::thread minimalpub([&](){
        rclcpp::spin(pub);
    });

    std::this_thread::sleep_for(10000ms);

    rclcpp::shutdown();
    minimalsubs.join();
    minimalout.join();
    minimalpub.join();

    std::ifstream ofile("samples3.out");
    ASSERT_GT(my_output.size(), 0);
    std::cout << "VECTOR SIZE IS: " << my_output.size() << std::endl;
    ASSERT_TRUE(ofile.is_open());
    double value;
    int i;
    for (i=0; !ofile.eof() && i < (int)my_output.size(); i++)
    {
        ofile >> value;
        std::cout << "the value is: " << value << " and the vector value is: " << my_output[i] << std::endl;
        ASSERT_FLOAT_EQ(value, my_output[i]);
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}