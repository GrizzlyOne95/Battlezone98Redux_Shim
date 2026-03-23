
void FUN_00625310(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 1 << ((char)param_4 - 1U & 0x1f);
  if (param_1 < -iVar1) {
    param_1 = -iVar1;
  }
  else if (iVar1 + -1 < param_1) {
    param_1 = iVar1 + -1;
  }
  FUN_00625220(param_1,param_2,param_3,param_4);
  return;
}

