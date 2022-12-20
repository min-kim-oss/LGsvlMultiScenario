#include "rclcpp/rclcpp.hpp"
#include "time.h"
#include <signal.h>
#include <termios.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include "std_msgs/msg/char.hpp"
#include "lgsvl_msgs/msg/vehicle_control_data.hpp"

#define KEYCODE_RIGHT 0x43
#define KEYCODE_LEFT 0x44
#define KEYCODE_UP 0x41
#define KEYCODE_DOWN 0x42

#define KEYCODE_A 0x61
#define KEYCODE_W 0x77
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64

#define CONTROL_PERIOD 0.1

class AgentController : public rclcpp::Node
{
  private:
    rclcpp::TimerBase::SharedPtr timer_control_;
    rclcpp::Subscription<std_msgs::msg::Char>::SharedPtr p1_key_sub;
    rclcpp::Publisher<lgsvl_msgs::msg::VehicleControlData>::SharedPtr cmd_pub;

    float max_steer_angle;
    float max_accel_input;
    float max_brake_input;

    float hit_increment;

    float cur_steer_angle;
    float cur_accel_input;
    float cur_brake_input;

    int max_hit_num;

    int uKey_hitCount;
    int dKey_hitCount;
    int steerKey_hitCount;
    

  public:
    explicit AgentController(const rclcpp::NodeOptions &);

    void timerCallBack();
    void hitRecoverer();
    void keyHandler(const std_msgs::msg::Char::SharedPtr);
    void cmd_creator();
    void cmd_publisher(float acc, float brk, float str);
};