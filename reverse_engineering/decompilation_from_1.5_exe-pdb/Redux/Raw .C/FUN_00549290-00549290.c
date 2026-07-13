
void __thiscall FUN_00549290(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = FUN_005c8800(param_2);
  if (iVar2 == 1) {
    cVar1 = FUN_005c8410(param_2,"svtank");
    if ((((cVar1 == '\0') && (cVar1 = FUN_005c8410(param_2,"svturr"), cVar1 == '\0')) &&
        (cVar1 = FUN_005c8410(param_2,"svfigh"), cVar1 == '\0')) &&
       (cVar1 = FUN_005c8410(param_2,"svwalk"), cVar1 == '\0')) {
      cVar1 = FUN_005c8410(param_2,"svscav");
      if ((cVar1 == '\0') && (cVar1 = FUN_005c8410(param_2,"svhaul"), cVar1 == '\0')) {
        return;
      }
      uVar3 = rand();
      uVar3 = uVar3 & 0x80000001;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
      }
      if (uVar3 == 0) {
        FUN_005cb9d0(param_2,*(undefined4 *)(param_1 + 0x84),0);
      }
      else {
        FUN_005cb9d0(param_2,*(undefined4 *)(param_1 + 0x88),0);
      }
      *(undefined4 *)(param_1 + 0x94) = param_2;
      return;
    }
    uVar3 = rand();
    uVar3 = uVar3 & 0x80000001;
    if ((int)uVar3 < 0) {
      uVar3 = (uVar3 - 1 | 0xfffffffe) + 1;
    }
    if (uVar3 == 0) {
      FUN_005cb820(param_2,*(undefined4 *)(param_1 + 0x84),0);
    }
    else {
      FUN_005cb820(param_2,*(undefined4 *)(param_1 + 0x88),0);
    }
    *(undefined4 *)(param_1 + 0x94) = param_2;
  }
  return;
}

