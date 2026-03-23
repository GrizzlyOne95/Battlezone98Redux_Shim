
undefined4 FUN_00429d60(char param_1)

{
  undefined1 local_8;
  
  if ((param_1 < 'A') || ('Z' < param_1)) {
    local_8 = param_1;
  }
  else {
    local_8 = param_1 + ' ';
  }
  return CONCAT31(param_1 >> 7,local_8);
}

