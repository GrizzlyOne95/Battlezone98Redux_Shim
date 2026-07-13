
undefined4 FUN_006ba8c0(undefined4 param_1,int param_2)

{
  if (param_2 == 1) {
    basic_string<>("Generic extension error");
  }
  else if (param_2 == 2) {
    basic_string<>("Use of methods from disabled extension");
  }
  else {
    basic_string<>("Unknown permessage-compress error");
  }
  return param_1;
}

