
undefined1 __thiscall FUN_00528370(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_24;
  int local_10;
  
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x62);
    uVar4 = 0x22;
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0xb8,0x88), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 0x77;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x144,0x1dc), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) &&
       (cVar2 = FUN_004ce910(param_2,param_1 + 0x324,0x3c,0xf,uVar3,uVar4), cVar2 != '\0')) {
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
    for (local_10 = 0; local_10 < 0x62; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x54) = 0;
    }
    for (local_10 = 0; local_10 < 0x22; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0xb8 + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 0x77; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x144 + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 0xf; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x324 + local_10 * 4) = 0;
    }
    FUN_005233b0();
    local_24 = FUN_0045d570(param_2);
  }
  return local_24;
}

