
uint __thiscall FUN_007f81b0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  
  cVar1 = FUN_007f5ad0(param_1);
  if (cVar1 == '\0') {
    uVar2 = FUN_007f88a0(param_1);
    cVar1 = FUN_007f88c0(param_2,uVar2);
    if (cVar1 == '\0') {
      uVar3 = FUN_007f7290(param_1);
      return uVar3 & 0xffffff00;
    }
  }
  return 1;
}

