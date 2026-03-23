
undefined4 __thiscall FUN_00512a40(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined1 local_30;
  char local_2c;
  
  cVar2 = FUN_004ce910(param_2,param_1 + 0x150,4);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x154,4), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x158,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x15c,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x160,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x164,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x168,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = 0;
  if ((bVar1) && (uVar3 = FUN_004ced10(param_2,param_1 + 0x16c,0xc), (uVar3 & 0xff) != 0)) {
    local_2c = '\x01';
  }
  else {
    local_2c = '\0';
  }
  uVar3 = CONCAT31((int3)(uVar3 >> 8),local_2c);
  if (local_2c != '\0') {
    uVar3 = FUN_004e73d0(param_2);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      local_30 = 1;
      goto LAB_00512c5d;
    }
  }
  local_30 = 0;
LAB_00512c5d:
  return CONCAT31((int3)(uVar3 >> 8),local_30);
}

