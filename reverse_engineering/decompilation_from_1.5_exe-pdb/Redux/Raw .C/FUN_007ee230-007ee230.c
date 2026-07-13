
uint __thiscall FUN_007ee230(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  
  cVar1 = FUN_007eb450(param_1);
  if (cVar1 == '\0') {
    uVar2 = FUN_007eef90(param_1);
    cVar1 = FUN_007eefb0(param_2,uVar2);
    if (cVar1 == '\0') {
      uVar3 = FUN_007ec9c0(param_1);
      return uVar3 & 0xffffff00;
    }
  }
  return 1;
}

