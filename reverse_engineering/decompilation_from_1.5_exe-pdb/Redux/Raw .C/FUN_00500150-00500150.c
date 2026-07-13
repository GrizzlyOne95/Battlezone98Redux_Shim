
bool FUN_00500150(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_004ff750(param_1,1);
  iVar2 = FUN_00462630(uVar1);
  if (iVar2 != 0) {
    uVar1 = FUN_004623e0();
    FUN_0082cd77(param_1,uVar1);
  }
  return iVar2 != 0;
}

