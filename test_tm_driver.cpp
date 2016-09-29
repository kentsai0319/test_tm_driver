#include "src/tm_driver/tm_driver.h"

#include <termios.h>
#include <math.h>

static struct termios oldt, newt;
/* Initialize new terminal i/o settings */
void initTermios(int echo) {
  tcgetattr(STDIN_FILENO, &oldt); /* grab old terminal i/o settings */
  newt = oldt; /* make new settings same as old settings */
  newt.c_lflag &= ~ICANON; /* disable buffered i/o */
  newt.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(STDIN_FILENO, TCSANOW, &newt); /* use these new terminal i/o settings now */
}
/* Restore old terminal i/o settings */
void resetTermios() {
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}
int kbhit() {
  struct timeval tv;
  fd_set rdfs;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);
  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);
}

void print_vectord(const std::vector<double>& vec) {
  for(int i = 0; i < vec.size() - 1; i++) {
    printf("%.4f, ", vec[i]);
  }
  printf("%.4f", vec[vec.size() - 1]);
}

void print_rt_1(const TmDriver& TR, double& time_s, std::vector<double>& vec) {
  time_s = TR.interface->stateRT->getQAct(vec);
  printf("[ INFO]  q_act:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
  time_s = TR.interface->stateRT->getQCmd(vec);
  printf("[ INFO]  q_cmd:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
}
void print_rt_2(const TmDriver& TR, double& time_s, std::vector<double>& vec) {
  time_s = TR.interface->stateRT->getQdAct(vec);
  printf("[ INFO] qd_act:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
  time_s = TR.interface->stateRT->getQdCmd(vec);
  printf("[ INFO] qd_cmd:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
}
void print_rt_3(const TmDriver& TR, double& time_s, std::vector<double>& vec) {
  time_s = TR.interface->stateRT->getQtAct(vec);
  printf("[ INFO] qt_act:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
  time_s = TR.interface->stateRT->getQtCmd(vec);
  printf("[ INFO] qt_cmd:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
}
void print_rt_4(const TmDriver& TR, double& time_s, std::vector<double>& vec) {
  time_s = TR.interface->stateRT->getTool0PosAct(vec);
  printf("[ INFO] tool0_pos_act:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
  time_s = TR.interface->stateRT->getTool0VelAct(vec);
  printf("[ INFO] tool0_vel_act:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
}
void print_rt_5(const TmDriver& TR, double& time_s, std::vector<double>& vec) {
  time_s = TR.interface->stateRT->getToolPosAct(vec);
  printf("[ INFO]  tool_pos_act:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
  time_s = TR.interface->stateRT->getToolPosCmd(vec);
  printf("[ INFO]  tool_pos_cmd:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
}
void print_rt_6(const TmDriver& TR, double& time_s, std::vector<double>& vec) {
  time_s = TR.interface->stateRT->getToolVelAct(vec);
  printf("[ INFO]  tool_vel_act:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
  time_s = TR.interface->stateRT->getToolVelCmd(vec);
  printf("[ INFO]  tool_vel_cmd:=< ");
  print_vectord(vec);
  printf(" > [%.3f]\n", time_s);
}
void print_rt_7(const TmDriver& TR, double& time_s, std::vector<double>& vec) {
  double val;
  bool isRA, isAE, isUW;
  time_s = TR.interface->stateRT->getTcpForce(vec);
  printf("[ INFO] tcp_force_est:=< ");
  print_vectord(vec);
  printf(" > [%.3f], ", time_s);
  time_s = TR.interface->stateRT->getTcpForceNorm(val);
  printf("norm:=%.4f  [%.3f]\n", val, time_s);
  TR.interface->stateRT->getKineConfig(isRA, isAE, isUW);
  //snprintf(_msg, 256, "kine_config:=< %d, %d, %d >", (int)isRA, (int)isAE, (int)isUW);
  print_info("kine_config:=< %d, %d, %d >", (int)isRA, (int)isAE, (int)isUW);
  val = TR.interface->stateRT->getSpdDownRatio();
  //snprintf(_msg, 256, "spd_down_ratio:=%.4f", val);
  print_info("spd_down_ratio:=%.4f", val);
  val = TR.interface->stateRT->getSpdJRatio();
  printf("[ INFO] spd_j: ratio:=%.4f, ", val);
  val = TR.interface->stateRT->getSpdJTa();
  printf("Ta:=%.4f\n", val);
  val = TR.interface->stateRT->getSpdLRatio();
  printf("[ INFO] spd_l: spd:=%.4f, ", val);
  val = TR.interface->stateRT->getSpdLTa();
  printf("Ta:=%.4f\n", val);
}
void print_rt_8(const TmDriver& TR) {
  std::vector<bool> vec;
  TR.interface->stateRT->getDigitalInputMB(vec);
  printf("[ INFO] MB DI: ");
  for(int i = 0; i < vec.size() - 1; i++) {
    printf("%d, ", (int)vec[i]);
  }
  printf("%d\n", (int)vec[vec.size() - 1]);
  TR.interface->stateRT->getDigitalOutputMB(vec);
  printf("[ INFO] MB DO: ");
  for(int i = 0; i < vec.size() - 1; i++) {
    printf("%d, ", (int)vec[i]);
  }
  printf("%d\n", (int)vec[vec.size() - 1]);
  TR.interface->stateRT->getDigitalInputEE(vec);
  printf("[ INFO] EE DI: ");
  for(int i = 0; i < vec.size() - 1; i++) {
    printf("%d, ", (int)vec[i]);
  }
  printf("%d\n", (int)vec[vec.size() - 1]);
  TR.interface->stateRT->getDigitalOutputEE(vec);
  printf("[ INFO] EE DO: ");
  for(int i = 0; i < vec.size() - 1; i++) {
    printf("%d, ", (int)vec[i]);
  }
  printf("%d\n", (int)vec[vec.size() - 1]);
}
void print_rt_9(const TmDriver& TR, double& time_s) {
  bool isErr;
  unsigned char ErrCode;
  print_info("robot_mode:=%d, safety_mode:=%d, teach_mode:=%d, control_mode:=%d",
    TR.interface->stateRT->getRobotMode(), TR.interface->stateRT->getSafetyMode(),
    TR.interface->stateRT->getTeachMode(), TR.interface->stateRT->getControlMode()
  );
  print_info("QueueCmdCount:=%d, BuffEmptyFlag:=%d",
    TR.interface->stateRT->getQueCmdCount(),
    TR.interface->stateRT->getBufEmptyFlag()
  );
  isErr = TR.interface->stateRT->getError(ErrCode, time_s);
  print_info("ErrorCode:=[%d][0x%x] [%.3f]",(int)isErr, ErrCode, time_s);
}

std::vector<double> parse_cmd(char* cstr, const char* delim, double& res) {
  std::vector<double> ret;
  //int count = 0;
  char* pch;
  char* pch_save;
  pch = strtok_r(cstr, delim, &pch_save);
  //printf("%d: %s\n", count, pch);
  if(pch != NULL) {
    while((pch = strtok_r(NULL, delim, &pch_save)) != NULL) {
      //count++;
      if(ret.size() < 6) {
	ret.push_back(atof(pch));
      }
      else {
	res = atof(pch);
	break;
      }
      //printf("%d: %s\n", count, pch);
    }
  }
  
  return ret;
}

int main(int argc, char **argv) {
  
  const int STDIN = 0;
  int sockfd = -1;
  bool fgRun = false;
  std::string host;
  std::condition_variable data_cv;
  std::condition_variable data_cv_rt;
  
  
  for(int i = 0; i < argc; i++) {
    printf("[DEBUG] arg%d:= %s\n", i, argv[i]);
  }
  host = argv[1];
  printf("[ INFO] host: %s", host.c_str());
  
  TmDriver TmRobot(data_cv, data_cv_rt, host, 0);
  
  char cstr[512];
  char delim[] = " ,;\t";
  char c;
  while(1) {
    memset(cstr, 0, 512);
    fgets(cstr, 512, stdin);
    int n = (int)strlen(cstr);
    if(n > 0) {
      if(cstr[n-1] == '\n')
	cstr[n-1] = '\0';
    }
    if(strncmp(cstr, "quit", 4) == 0) {
      TmRobot.interface->halt();
      fgRun = false;
      print_info("quit");
      std::this_thread::sleep_for(std::chrono::milliseconds(25));
      break;
    }
    else if(strncmp(cstr, "start", 5) == 0) {
      if(!fgRun) {
	print_info("start...");
	fgRun = TmRobot.interface->start();
      }
    }
    else if(strncmp(cstr, "halt", 4) == 0) {
      print_info("halt");
      TmRobot.interface->halt();
      fgRun = false;
    }
    else if(strncmp(cstr, "data", 4) == 0) {
      double temp_time;
      std::vector<double> temp_vec;
      if(cstr[4] == '\0') {
	print_info("data");
      }
      else {
	print_info("datart");
	print_info("1:");
	print_rt_1(TmRobot, temp_time, temp_vec);
	print_info("2:");
	print_rt_2(TmRobot, temp_time, temp_vec);
	print_info("3:");
	print_rt_3(TmRobot, temp_time, temp_vec);
	print_info("4:");
	print_rt_4(TmRobot, temp_time, temp_vec);
	print_info("5:");
	print_rt_5(TmRobot, temp_time, temp_vec);
	print_info("6:");
	print_rt_6(TmRobot, temp_time, temp_vec);
	print_info("7:");
	print_rt_7(TmRobot, temp_time, temp_vec);
	print_info("8:");
	print_rt_8(TmRobot);
	print_info("9:");
	print_rt_9(TmRobot, temp_time);
      }
    }
    else if(strncmp(cstr, "show", 6) == 0) {
      char temp_c = '0';
      double temp_time;
      std::vector<double> temp_vec;
      initTermios(1);
      while(1) {
	if(kbhit()) {
	  c = getchar();
	  if(c == 'q' || c == 'Q')
	    break;
	  temp_c = c;
	}
	switch(temp_c) {
	  default:
	    temp_time = TmRobot.interface->stateRT->getTime();
	    printf("[ INFO] [%.3f]\n", temp_time);
	    break;
	  case '1':
	    print_rt_1(TmRobot, temp_time, temp_vec);
	    printf("\n");
	    break;
	  case '2':
	    print_rt_2(TmRobot, temp_time, temp_vec);
	    printf("\n");
	    break;
	  case '3':
	    print_rt_3(TmRobot, temp_time, temp_vec);
	    printf("\n");
	    break;
	  case '4':
	    print_rt_4(TmRobot, temp_time, temp_vec);
	    printf("\n");
	    break;
	  case '5':
	    print_rt_5(TmRobot, temp_time, temp_vec);
	    printf("\n");
	    break;
	  case '6':
	    print_rt_6(TmRobot, temp_time, temp_vec);
	    printf("\n");
	    break;
	  case '7':
	    print_rt_7(TmRobot, temp_time, temp_vec);
	    printf("\n");
	    break;
	  case '8':
	    print_rt_8(TmRobot);
	    printf("\n");
	    break;
	  case'9':
	    print_rt_9(TmRobot, temp_time);
	    printf("\n");
	    break;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(25));
      }
      resetTermios();
      printf("\n");
    }
    else if(strncmp(cstr, "clear", 5) == 0) {
      system("clear");
    }
    else if(strncmp(cstr, "movjabs", 7) == 0) {
      double blend = 0;
      std::vector<double> vec = parse_cmd(cstr, delim, blend);
      TmRobot.setMoveJabs(vec, blend);
    }
    else if(strncmp(cstr, "movjrel", 7) == 0) {
      double blend = 0;
      std::vector<double> vec = parse_cmd(cstr, delim, blend);
      TmRobot.setMoveJrel(vec, blend);
    }
    else if(strncmp(cstr, "movlabs", 7) == 0) {
      double blend = 0;
      std::vector<double> vec = parse_cmd(cstr, delim, blend);
      TmRobot.setMoveLabs(vec, blend);
    }
    else if(strncmp(cstr, "movlrel", 7) == 0) {
      double blend = 0;
      std::vector<double> vec = parse_cmd(cstr, delim, blend);
      TmRobot.setMoveLrel(vec, blend);
    }
    else if(strncmp(cstr, "testservoj", 10) == 0) {
      int axis = 0;
      double timeval = 0.01, period = 10.0, amp = M_PI/6.0, jog_init;
      float cmd_data[4] = {0,0,0,0};
      int count = 0;
      char* pch;
      char* pch_save;
      pch = strtok_r(cstr, delim, &pch_save);
      if(pch != NULL) {
	while((pch = strtok_r(NULL, delim, &pch_save)) != NULL) {
	  if(count < 4) {
	    cmd_data[count] = atof(pch);
	  }
	  else {
	    break;
	  }
	  count++;
	}
      }
      if(count > 0)
	axis = (int)cmd_data[0];
      if(axis < 0)
	axis = 0;
      else if(axis > 6)
	axis = 6;
      if(cmd_data[1] != 0)
	timeval = cmd_data[1];
      if(cmd_data[2] != 0)
	period = cmd_data[2];
      if(cmd_data[3] != 0)
	amp = cmd_data[3];

      print_info("testservoj start... [q] to quit");
      
      TmRobot.setServoOpen("srvj");
      
      std::vector<double> jog_vec;
      TmRobot.interface->stateRT->getQAct(jog_vec);
      jog_init = jog_vec[axis];
      
      count = 0;
      initTermios(1);
      while(1) {
	if(kbhit()) {
	  c = getchar();
	  if(c == 'q' || c == 'Q')
	    break;
	}
	jog_vec[axis] = jog_init + amp - amp * cos((2.0 * M_PI / period) * timeval * (double)count);
	TmRobot.setServoj(jog_vec);
	std::this_thread::sleep_for(std::chrono::milliseconds((int)(timeval * 1000.0)));
	count++;
      }
      resetTermios();
      
      TmRobot.setServoClose();
      
      print_info("\ntestservoj stop");
    }
    else {
      print_info("send cmd...");
      std::string msg(cstr);
      TmRobot.setCommandMsg(msg);
    }
  }
  return 0;
}
