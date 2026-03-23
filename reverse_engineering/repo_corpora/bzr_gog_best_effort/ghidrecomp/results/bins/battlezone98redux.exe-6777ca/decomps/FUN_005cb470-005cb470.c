
undefined4 FUN_005cb470(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = *(int *)(&DAT_02a13d20 + param_1 * 4);
  if ((iVar1 < 0) || (DAT_02a13d84 <= iVar1)) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_005ce740(iVar1);
  }
  return uVar2;
}

