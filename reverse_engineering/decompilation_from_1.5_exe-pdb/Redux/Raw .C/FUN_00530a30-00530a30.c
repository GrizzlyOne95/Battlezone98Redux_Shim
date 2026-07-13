
undefined1 __thiscall FUN_00530a30(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_24;
  int local_10;
  
  FUN_005c9470(1,3);
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x2c);
    uVar4 = 0x21;
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x84,0x84), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 0x29;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x10c,0xa4), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x1b4,8,2,uVar3,uVar4), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_0045d570(param_2), cVar2 != '\0')) {
      local_24 = 1;
    }
    else {
      local_24 = 0;
    }
  }
  else {
    for (local_10 = 0; local_10 < 0x2c; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x54) = 0;
    }
    for (local_10 = 0; local_10 < 0x21; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x84 + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 0x29; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x10c + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 2; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x1b4 + local_10 * 4) = 0;
    }
    FUN_0052dbf0();
    local_24 = FUN_0045d570(param_2);
  }
  return local_24;
}

