
void FUN_00771030(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
    FUN_00771b60(&local_18,param_1,param_2,param_3,param_4,param_6);
    param_5 = (param_5 / 2) / 2 + param_5 / 2;
    iVar1 = FUN_00732ef0(&param_1);
    iVar2 = FUN_00732ef0(&local_10);
    if (iVar1 < iVar2) {
      FUN_00771030(param_1,param_2,local_18,local_14,param_5,param_6);
      param_1 = local_10;
      param_2 = local_c;
    }
    else {
      FUN_00771030(local_10,local_c,param_3,param_4,param_5,param_6);
      param_3 = local_18;
      param_4 = local_14;
    }
  }
  if (local_8 < 0x21) {
    if (1 < local_8) {
      FUN_00772080(param_1,param_2,param_3,param_4,param_6);
    }
  }
  else {
    FUN_00771fb0(param_1,param_2,param_3,param_4,param_6);
    FUN_00772030(param_1,param_2,param_3,param_4,param_6);
  }
  return;
}

