
int FUN_00833b59(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_0082c225(param_1,1,0,0);
  iVar2 = FUN_0082c8f6(param_1);
  iVar3 = FUN_0082be9b(param_1,uVar1);
  if (iVar3 != 0) {
    FUN_0082c6fb(param_1);
  }
  FUN_0082c585(param_1,0,0xffffffff);
  iVar3 = FUN_0082c8f6(param_1);
  return iVar3 - iVar2;
}

