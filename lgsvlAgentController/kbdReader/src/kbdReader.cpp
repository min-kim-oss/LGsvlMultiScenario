#include "kbdReader/kbdReader.hpp"

KBDReader::KBDReader(std::shared_ptr<rclcpp::Node> nh) : nh_(nh)
{
    kfd = 0;

    

    while(true){
      std::cout<<"Choose number of vehicle to control(1 or 2) : ";
      std::cin >> agent_num;

      if(agent_num == 1){
       p1_key_pub = nh_->create_publisher<std_msgs::msg::Char>("/player1/kbd_cmd", 1);
        break;
      }
      else if(agent_num == 2){
        p1_key_pub = nh_->create_publisher<std_msgs::msg::Char>("/player1/kbd_cmd", 1);
        p2_key_pub = nh_->create_publisher<std_msgs::msg::Char>("/player2/kbd_cmd", 1);
        break;
      }
      else{
        std::cout<<"you need to choose between 1 and 2"<<std::endl;
        continue;
      }
    }

    // get the console in raw mode                                                              
    tcgetattr(kfd, &cooked);
    memcpy(&raw, &cooked, sizeof(struct termios));
    raw.c_lflag &=~ (ICANON | ECHO);
    // Setting a new line, then end of file                         
    raw.c_cc[VEOL] = 1;
    raw.c_cc[VEOF] = 2;
    tcsetattr(kfd, TCSANOW, &raw);

}

int KBDReader::keyLoop()
{
  char c;
  p1_dirty=false;
  p2_dirty=false;

  std::cout<<"Reading from keyboard"<<std::endl;
  std::cout<<"---------------------------"<<std::endl;
  if(agent_num == 1){
    std::cout<<"Use arrow keys to move the vehicle."<<std::endl;
  }
  else{
    std::cout<<"Use arrow keys to move the player 1 vehicle."<<std::endl;
    std::cout<<"Use w a s d to move the player 2 vehicle."<<std::endl;
  }

  for(;;)
  {
    //get the next event from the keyboard  
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    switch(c)
    {
      case KEYCODE_UP:
      case KEYCODE_LEFT:
      case KEYCODE_DOWN:
      case KEYCODE_RIGHT:
        p1_dirty = true;
        break;
      
      case KEYCODE_W:
      case KEYCODE_A:
      case KEYCODE_S:
      case KEYCODE_D:
        if(agent_num == 2 ){
          p2_dirty = true;
          
        }
        break;
        
      case KEYCODE_Q:
        std::cout << "QUIT" << std::endl;
        return 0;
      default:
        break;
    }
    if(p1_dirty ==true ||p2_dirty == true)
    {
      key_publisher(c);
    }
    
  }
  return 0;
}

void KBDReader::key_publisher(char key)
{
  std_msgs::msg::Char msg;
  msg.data = key;
  if(p1_dirty){
    p1_key_pub->publish(msg);
    p1_dirty=false;
  }
  else if(p2_dirty){
    p2_key_pub->publish(msg);
    p2_dirty=false;
  }

}