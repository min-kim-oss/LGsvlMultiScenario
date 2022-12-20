#include "agentController/p2AgentController.hpp"

P2AgentController::P2AgentController(const rclcpp::NodeOptions & options)
    : rclcpp::Node("P2AgentController", options)
{
  p2_key_sub = this->create_subscription<std_msgs::msg::Char>(
    "/player2/kbd_cmd",10,std::bind(&P2AgentController::keyHandler,this,std::placeholders::_1));

  cmd_pub = this->create_publisher<lgsvl_msgs::msg::VehicleControlData>("/player2/vehicle_control_cmd", 1);

  max_steer_angle = 0.68; //39.4  
  max_accel_input = 1.0;
  max_brake_input = 1.0;

  hit_increment = 1.0;

  cur_steer_angle = 0;
  cur_accel_input = 0;
  cur_brake_input = 0;

  max_hit_num = 50;

  uKey_hitCount = 0;
  dKey_hitCount = 0;
  steerKey_hitCount = 0;

   // Timer
  {
    const auto period_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(
      std::chrono::duration<double>(CONTROL_PERIOD));
    timer_control_ = rclcpp::create_timer(
      this, get_clock(), period_ns, std::bind(&P2AgentController::timerCallBack, this));
  }
}

void P2AgentController::timerCallBack()
{
  hitRecoverer();
}

void P2AgentController::hitRecoverer()
{ 
  std::cout << "recovering" << std::endl;
  //uKey_hitCount recover 
  if(uKey_hitCount > 0)
  {
    uKey_hitCount -= hit_increment;
  } 
  else if(uKey_hitCount < 0)
  {
    uKey_hitCount = 0;
  }

  if(steerKey_hitCount > 0)
  {
    steerKey_hitCount -= hit_increment;
  }
  else if(steerKey_hitCount < 0)
  {
    steerKey_hitCount += hit_increment;
  }
  else if(steerKey_hitCount < hit_increment && steerKey_hitCount > -hit_increment)
  {
    steerKey_hitCount = 0;
  }
  dKey_hitCount = 0;

  cmd_creator();
}



void P2AgentController::keyHandler(const std_msgs::msg::Char::SharedPtr msg)
{
  char key = msg->data;
  
  std::cout << "receiving" << std::endl;


  switch(key)
  {
    case KEYCODE_W:
      std::cout << "up key" << std::endl;
      if(uKey_hitCount + hit_increment < max_hit_num){
        uKey_hitCount += hit_increment;
      }
      break;
    case KEYCODE_S:
      std::cout << "down key" << std::endl;
      dKey_hitCount = max_hit_num;
      uKey_hitCount = 0;
      break;
    case KEYCODE_A:
      std::cout << "left key" << std::endl;
      if(steerKey_hitCount - hit_increment > -max_hit_num){
        steerKey_hitCount -= hit_increment;
      }
      break;
    case KEYCODE_D:
      std::cout << "right key" << std::endl;
      if(steerKey_hitCount + hit_increment < max_hit_num){
        steerKey_hitCount += hit_increment;
      }
      break;
  }

  cmd_creator();
}

void P2AgentController::cmd_creator()
{
  std::cout << "ukey hit count" << uKey_hitCount <<std::endl;
  std::cout << "steerKey hit count" << steerKey_hitCount <<std::endl;
  std::cout << "dkey hit count" << dKey_hitCount <<std::endl;

  cur_accel_input =  max_accel_input * ((float)uKey_hitCount/max_hit_num);
  
  cur_steer_angle = max_steer_angle * ((float)steerKey_hitCount/max_hit_num);
  
  cur_brake_input = max_brake_input * ((float)dKey_hitCount/max_hit_num);
  

  cmd_publisher(cur_accel_input, cur_brake_input, cur_steer_angle);
}

void P2AgentController::cmd_publisher(float acc, float brk, float str){
  lgsvl_msgs::msg::VehicleControlData msg;
  msg.acceleration_pct = acc;
  msg.braking_pct = brk;
  msg.target_wheel_angle = str;
  cmd_pub->publish(msg);
}

