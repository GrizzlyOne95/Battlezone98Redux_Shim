
undefined4 FUN_00432410(char param_1)

{
  undefined1 local_8;
  
  if ((param_1 == ';') || (param_1 == '#')) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return CONCAT31(param_1 >> 7,local_8);
}

