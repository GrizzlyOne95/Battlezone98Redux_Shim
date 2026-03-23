
void FUN_00670270(int param_1,int param_2,int param_3,undefined1 param_4)

{
  int local_10;
  int local_c;
  int local_8;
  
  while ((local_8 = (param_2 - param_1) / 0x1c, 0x20 < local_8 && (0 < param_3))) {
    FUN_00673710(&local_10,param_1,param_2,param_4);
    param_3 = (param_3 / 2) / 2 + param_3 / 2;
    if ((local_10 - param_1) / 0x1c < (param_2 - local_c) / 0x1c) {
      FUN_00670270(param_1,local_10,param_3,param_4);
      param_1 = local_c;
    }
    else {
      FUN_00670270(local_c,param_2,param_3,param_4);
      param_2 = local_10;
    }
  }
  if (local_8 < 0x21) {
    if (1 < local_8) {
      FUN_00673a70(param_1,param_2,param_4);
    }
  }
  else {
    FUN_006739e0(param_1,param_2,param_4);
    FUN_00673a40(param_1,param_2,param_4);
  }
  return;
}

