
undefined1 __thiscall FUN_00547610(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 local_28;
  int local_14;
  int local_10;
  
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x18);
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x70,0x28), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    for (local_14 = 0; local_14 < 10; local_14 = local_14 + 1) {
      if (*(float *)(param_1 + 0x70 + local_14 * 4) == 9999.0) {
        *(undefined4 *)(param_1 + 0x70 + local_14 * 4) = 0x47c34f80;
      }
    }
    uVar3 = 0x16;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x9c,0x58), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0xf8,4,1,uVar3), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_0045d570(param_2), cVar2 != '\0')) {
      local_28 = 1;
    }
    else {
      local_28 = 0;
    }
  }
  else {
    for (local_10 = 0; local_10 < 0x18; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x54) = 0;
    }
    for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x70 + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 0x16; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x9c + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 1; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0xf8 + local_10 * 4) = 0;
    }
    FUN_005456a0();
    local_28 = FUN_0045d570(param_2);
  }
  return local_28;
}

