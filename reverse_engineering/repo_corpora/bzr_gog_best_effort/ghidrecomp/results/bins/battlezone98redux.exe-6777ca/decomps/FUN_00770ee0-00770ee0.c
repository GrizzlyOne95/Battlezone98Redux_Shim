
void FUN_00770ee0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5,undefined1 param_6)

{
  int iVar1;
  int iVar2;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  int local_8;
  
  while ((local_8 = FUN_00732ef0(&param_1), 0x20 < local_8 && (0 < param_5))) {
    FUN_00771600(&local_18,param_1,param_2,param_3,param_4,param_6);
    param_5 = (param_5 / 2) / 2 + param_5 / 2;
    iVar1 = FUN_00732ef0(&param_1);
    iVar2 = FUN_00732ef0(&local_10);
    if (iVar1 < iVar2) {
      FUN_00770ee0(param_1,param_2,local_18,local_14,param_5,param_6);
      param_1 = local_10;
      param_2 = local_c;
    }
    else {
      FUN_00770ee0(local_10,local_c,param_3,param_4,param_5,param_6);
      param_3 = local_18;
      param_4 = local_14;
    }
  }
  if (local_8 < 0x21) {
    if (1 < local_8) {
      FUN_00771b20(param_1,param_2,param_3,param_4,param_6);
    }
  }
  else {
    FUN_00771a50(param_1,param_2,param_3,param_4,param_6);
    FUN_00771ad0(param_1,param_2,param_3,param_4,param_6);
  }
  return;
}

