
void FUN_008387f7(undefined4 param_1,undefined4 param_2,int *param_3,uint param_4,int param_5,
                 undefined4 param_6)

{
  int iVar1;
  
  iVar1 = *param_3;
  if (iVar1 < param_5 / 2) {
    param_5 = iVar1 * 2;
    if (iVar1 * 2 < 4) {
      param_5 = 4;
    }
  }
  else if (param_5 <= iVar1) {
    FUN_0082df5b(param_1,param_6);
  }
  if (0xfffffffd / param_4 < param_5 + 1U) {
    FUN_008388ab(param_1);
  }
  else {
    FUN_00838869(param_1,param_2,*param_3 * param_4,param_5 * param_4);
  }
  *param_3 = param_5;
  return;
}

