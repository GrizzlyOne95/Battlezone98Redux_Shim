
void FUN_00673550(int param_1,int param_2,int param_3,undefined1 param_4)

{
  int local_10;
  int local_c;
  int local_8;
  
  while ((local_8 = (param_2 - param_1) / 0x18, 0x20 < local_8 && (0 < param_3))) {
    FUN_00675850(&local_10,param_1,param_2,param_4);
    param_3 = (param_3 / 2) / 2 + param_3 / 2;
    if ((local_10 - param_1) / 0x18 < (param_2 - local_c) / 0x18) {
      FUN_00673550(param_1,local_10,param_3,param_4);
      param_1 = local_c;
    }
    else {
      FUN_00673550(local_c,param_2,param_3,param_4);
      param_2 = local_10;
    }
  }
  if (local_8 < 0x21) {
    if (1 < local_8) {
      FUN_00675bb0(param_1,param_2,param_4);
    }
  }
  else {
    FUN_00675b20(param_1,param_2,param_4);
    FUN_00675b80(param_1,param_2,param_4);
  }
  return;
}

