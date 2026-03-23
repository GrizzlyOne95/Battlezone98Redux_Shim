
void __thiscall FUN_004ff260(undefined4 param_1,undefined4 param_2,int *param_3,int param_4)

{
  int iVar1;
  
  FUN_0082bb89(param_2,param_4,"too many upvalues",param_1);
  for (; *param_3 != 0; param_3 = param_3 + 2) {
    for (iVar1 = 0; iVar1 < param_4; iVar1 = iVar1 + 1) {
      FUN_0082cdd2(param_2,-param_4);
    }
    FUN_0082cd77(param_2,*param_3);
    FUN_0082cc15(param_2,param_3[1],param_4);
    FUN_0082d1fa(param_2,-(param_4 + 3));
  }
  FUN_0082d226(param_2,-1 - param_4);
  return;
}

