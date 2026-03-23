
undefined1 __thiscall FUN_006487e0(int param_1,undefined4 param_2)

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
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,10);
    uVar4 = 9;
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x60,0x24), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 0x68;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x88,0x1a0), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x22c,0x20,8,uVar3,uVar4), cVar2 != '\0')
       ) {
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
    for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x54) = 0;
    }
    for (local_10 = 0; local_10 < 9; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x60 + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 0x68; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x88 + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x22c + local_10 * 4) = 0;
    }
    FUN_00648d80();
    local_24 = FUN_0045d570(param_2);
  }
  return local_24;
}

