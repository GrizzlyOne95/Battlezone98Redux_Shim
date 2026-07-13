
undefined4 FUN_0068fa90(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0068fa60(param_1);
  if ((iVar1 == 0) || (*(int *)(&DAT_00930f28 + param_1 * 4) != 1)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

