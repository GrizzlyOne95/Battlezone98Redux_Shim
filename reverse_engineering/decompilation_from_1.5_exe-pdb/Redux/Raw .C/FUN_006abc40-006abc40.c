
undefined4 FUN_006abc40(undefined4 param_1,int param_2)

{
  if (param_2 == 1) {
    basic_string<>("Already open");
  }
  else if (param_2 == 2) {
    basic_string<>("End of file");
  }
  else if (param_2 == 3) {
    basic_string<>("Element not found");
  }
  else if (param_2 == 4) {
    basic_string<>("The descriptor does not fit into the select call\'s fd_set");
  }
  else {
    basic_string<>("asio.misc error");
  }
  return param_1;
}

