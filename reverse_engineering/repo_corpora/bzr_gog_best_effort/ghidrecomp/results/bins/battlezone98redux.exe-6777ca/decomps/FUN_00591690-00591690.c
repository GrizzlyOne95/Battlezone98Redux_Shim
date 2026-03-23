
uint FUN_00591690(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 uVar2;
  uint uVar3;
  int iVar4;
  
  cVar1 = FUN_0046adb0(param_1,param_2);
  if (cVar1 == '\0') {
    uVar3 = 6;
  }
  else {
    uVar2 = FUN_0046acc0(param_1,param_2);
    uVar3 = FUN_00591670(uVar2);
    if ((uVar3 == 0) || (uVar3 == 1)) {
      iVar4 = FUN_0046ad30(param_1,param_2);
      uVar3 = iVar4 << 0x10 | uVar3;
    }
  }
  return uVar3;
}

