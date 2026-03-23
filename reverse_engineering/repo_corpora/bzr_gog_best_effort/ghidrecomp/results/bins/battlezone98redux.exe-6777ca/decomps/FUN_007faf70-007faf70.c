
undefined4 FUN_007faf70(uint param_1)

{
  undefined1 local_5;
  
  if (((param_1 & 0xffffff00) == 0) || ((param_1 | 0xff) == 0xffffffff)) {
    local_5 = 1;
  }
  else {
    local_5 = 0;
  }
  return CONCAT31((int3)((param_1 & 0xffffff00) >> 8),local_5);
}

