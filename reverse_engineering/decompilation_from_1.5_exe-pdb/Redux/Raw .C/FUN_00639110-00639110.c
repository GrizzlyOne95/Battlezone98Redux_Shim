
undefined1 __thiscall FUN_00639110(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined1 local_24;
  int local_10;
  
  uVar4 = 1;
  FUN_007647a0(1);
  cVar2 = FUN_007537a0(uVar4);
  if (cVar2 == '\0') {
    local_24 = 0;
  }
  else if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,4);
    uVar4 = 4;
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x5c,0x10), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 0x28;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x70,0xa0), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x114,8,2,uVar3,uVar4), cVar2 != '\0')) {
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
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x54) = 0;
    }
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x5c + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 0x28; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x70 + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 2; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x114 + local_10 * 4) = 0;
    }
    FUN_00639760();
    local_24 = FUN_0045d570(param_2);
  }
  return local_24;
}

