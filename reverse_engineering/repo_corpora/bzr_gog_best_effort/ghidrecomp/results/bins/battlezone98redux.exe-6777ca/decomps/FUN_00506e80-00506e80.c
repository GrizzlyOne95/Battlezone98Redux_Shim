
bool FUN_00506e80(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_0082d377(param_1,1,0);
  iVar2 = FUN_00481af0(uVar1);
  if (iVar2 != 0) {
    uVar3 = FUN_00481a60(uVar1);
    FUN_0082cd08(param_1,iVar2,uVar3);
    FUN_00481990(uVar1);
  }
  return iVar2 != 0;
}

