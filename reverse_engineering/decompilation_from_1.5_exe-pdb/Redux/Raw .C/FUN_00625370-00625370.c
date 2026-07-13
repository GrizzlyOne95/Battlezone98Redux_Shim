
void FUN_00625370(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 1 << ((byte)param_4 & 0x1f);
  if (param_1 < 0) {
    param_1 = 0;
  }
  else if (iVar1 + -1 < param_1) {
    param_1 = iVar1 + -1;
  }
  FUN_00625220(param_1,param_2,param_3,param_4);
  return;
}

