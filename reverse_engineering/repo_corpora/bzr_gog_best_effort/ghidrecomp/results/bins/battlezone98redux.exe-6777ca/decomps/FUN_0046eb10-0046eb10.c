
void FUN_0046eb10(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = DAT_0260d634 * 0x10;
  DAT_0260d634 = DAT_0260d634 + 1;
  *(undefined4 *)(&DAT_0260d5f0 + iVar1) = param_1;
  *(undefined4 *)(&DAT_0260d5f4 + iVar1) = param_2;
  *(undefined4 *)(&DAT_0260d5f8 + iVar1) = param_3;
  *(undefined4 *)(&DAT_0260d5fc + iVar1) = param_4;
  return;
}

