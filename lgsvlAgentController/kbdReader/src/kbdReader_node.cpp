#include <memory>
#include "kbdReader/kbdReader.hpp"

int main(int argc, char** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("kbdReader");
  KBDReader reader(node);

  reader.keyLoop();
}