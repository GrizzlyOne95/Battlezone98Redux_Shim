
undefined4 __thiscall FUN_0064cce0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 local_28;
  char local_24;
  undefined4 local_1c;
  int local_10;
  
  uVar4 = 1;
  FUN_007647a0(1);
  cVar2 = FUN_007537a0(uVar4);
  if (cVar2 == '\0') {
    return 0;
  }
  if (DAT_009173b7 != '\0') {
    for (local_10 = 0; local_10 < 0x17; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x54) = 0;
    }
    for (local_10 = 0; local_10 < 0xb; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x6c + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 0x19; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x9c + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x104 + local_10 * 4) = 0;
    }
    FUN_0064d2a0();
    uVar4 = FUN_0045d570(param_2);
    return uVar4;
  }
  cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x17);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x6c,0x2c), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  local_1c = 100;
  memset((void *)(param_1 + 0x9c),0,100);
  if (DAT_00917b20 < 0x7db) {
    local_1c = 0x54;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x9c,local_1c), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = 0;
  if ((bVar1) && (uVar3 = FUN_004ce910(param_2,param_1 + 0x104,0x10,4), (uVar3 & 0xff) != 0)) {
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
      goto LAB_0064cfe6;
    }
  }
  local_28 = 0;
LAB_0064cfe6:
  return CONCAT31((int3)(uVar3 >> 8),local_28);
}

