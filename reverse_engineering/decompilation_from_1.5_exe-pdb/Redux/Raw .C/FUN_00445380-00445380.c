
int FUN_00445380(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 *param_7,undefined4 param_8,
                undefined4 *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13)

{
  int iVar1;
  
  iVar1 = param_7[9];
  if (iVar1 == 1) {
    iVar1 = FUN_004454a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,
                         param_11,param_12,1,0);
    if (iVar1 != 0) {
      *param_9 = *param_7;
    }
  }
  else if (iVar1 == 2) {
    iVar1 = 1;
    *param_9 = *param_7;
  }
  else if (iVar1 == 3) {
    iVar1 = FUN_00445610(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10,param_11,param_12,param_13);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

