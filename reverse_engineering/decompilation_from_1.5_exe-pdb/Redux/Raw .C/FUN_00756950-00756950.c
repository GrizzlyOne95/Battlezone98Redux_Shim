
void FUN_00756950(int param_1,int param_2,int param_3,undefined1 param_4)

{
  int local_10;
  int local_c;
  int local_8;
  
  while ((local_8 = (param_2 - param_1) / 0x50, 0x20 < local_8 && (0 < param_3))) {
    FUN_00756ca0(&local_10,param_1,param_2,param_4);
    param_3 = (param_3 / 2) / 2 + param_3 / 2;
    if ((local_10 - param_1) / 0x50 < (param_2 - local_c) / 0x50) {
      FUN_00756950(param_1,local_10,param_3,param_4);
      param_1 = local_c;
    }
    else {
      FUN_00756950(local_c,param_2,param_3,param_4);
      param_2 = local_10;
    }
  }
  if (local_8 < 0x21) {
    if (1 < local_8) {
      FUN_00757000(param_1,param_2,param_4);
    }
  }
  else {
    FUN_00756f70(param_1,param_2,param_4);
    FUN_00756fd0(param_1,param_2,param_4);
  }
  return;
}

