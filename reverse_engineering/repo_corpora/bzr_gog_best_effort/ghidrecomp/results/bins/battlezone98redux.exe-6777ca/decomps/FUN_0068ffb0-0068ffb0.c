
void FUN_0068ffb0(undefined4 param_1,int *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_00920f04 + *param_2 * 4);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0xb8) = *(int *)(iVar1 + 0xb8) - param_3;
    iVar1 = param_2[7];
    if ((1 < iVar1) && ((iVar1 < 4 || (iVar1 == 7)))) {
      param_2[9] = param_2[9] - param_3;
    }
  }
  return;
}

