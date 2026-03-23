
undefined4 FUN_00838404(undefined4 param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = FUN_00838733(param_1,1);
  for (iVar2 = FUN_0082c8f6(param_1); 1 < iVar2; iVar2 = iVar2 + -1) {
    uVar3 = FUN_00838733(param_1,iVar2);
    uVar1 = uVar1 & uVar3;
  }
  FUN_0082cd58(param_1,(double)(int)uVar1);
  return 1;
}

