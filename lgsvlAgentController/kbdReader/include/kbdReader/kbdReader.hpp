#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include "std_msgs/msg/char.hpp"
#include "rclcpp/rclcpp.hpp"


// keycode from showkey -a
#define KEYCODE_1 0x31
#define KEYCODE_2 0x32

#define KEYCODE_RIGHT 0x43
#define KEYCODE_LEFT 0x44
#define KEYCODE_UP 0x41
#define KEYCODE_DOWN 0x42

#define KEYCODE_A 0x61
#define KEYCODE_W 0x77
#define KEYCODE_S 0x73
#define KEYCODE_D 0x64

#define KEYCODE_Q 0x71


class KBDReader
{
  private:
    std::shared_ptr<rclcpp::Node> nh_;
    rclcpp::Publisher<std_msgs::msg::Char>::SharedPtr p1_key_pub;
    rclcpp::Publisher<std_msgs::msg::Char>::SharedPtr p2_key_pub;

  public:
    int kfd;
    int agent_num;
    struct termios cooked, raw;
    bool p1_dirty;
    bool p2_dirty;

    KBDReader(std::shared_ptr<rclcpp::Node> nh);
    int keyLoop();
    void key_publisher(char key);
};