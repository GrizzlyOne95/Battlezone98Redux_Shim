
undefined4 FUN_00432e00(char param_1)

{
  undefined1 local_8;
  
  if ((param_1 == '\n') || (param_1 == '\r')) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return CONCAT31(param_1 >> 7,local_8);
}

