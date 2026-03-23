
undefined4 __thiscall FUN_00650b20(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 local_28;
  char local_24;
  undefined4 local_18;
  int local_10;
  
  uVar4 = 1;
  FUN_007647a0(1);
  cVar2 = FUN_007537a0(uVar4);
  if (cVar2 == '\0') {
    return 0;
  }
  if (DAT_009173b7 != '\0') {
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x55) = 0;
    }
    for (local_10 = 0; local_10 < 3; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x5c + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 0x59; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x6c + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x1d4 + local_10 * 4) = 0;
    }
    FUN_006513b0();
    uVar4 = FUN_0045d570(param_2);
    return uVar4;
  }
  cVar2 = FUN_004ce5e0(param_2,param_1 + 0x55,4);
  local_18 = 0xc;
  if (DAT_00917b20 < 0x7db) {
    *(undefined4 *)(param_1 + 100) = 0x47c34f80;
    local_18 = 8;
  }
  if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x5c,local_18), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  uVar4 = 0x59;
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x6c,0x164), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = 0;
  if ((bVar1) && (uVar3 = FUN_004ce910(param_2,param_1 + 0x1d4,0x14,5,uVar4), (uVar3 & 0xff) != 0))
  {
    local_24 = '\x01';
  }
  else {
    local_24 = '\0';
  }
  uVar3 = CONCAT31((int3)(uVar3 >> 8),local_24);
  if (local_24 != '\0') {
    uVar3 = FUN_0045d570(param_2);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      local_28 = 1;
      goto LAB_00650e0d;
    }
  }
  local_28 = 0;
LAB_00650e0d:
  return CONCAT31((int3)(uVar3 >> 8),local_28);
}

