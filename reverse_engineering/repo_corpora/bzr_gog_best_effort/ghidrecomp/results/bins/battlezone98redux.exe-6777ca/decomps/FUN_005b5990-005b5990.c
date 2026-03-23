
undefined4 __thiscall FUN_005b5990(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined1 local_44;
  char local_40;
  
  cVar2 = FUN_004cf640(param_2,param_1 + 0x2c,4,"RecycleTask::me",param_1);
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cf640(param_2,param_1 + 0x30,4,"RecycleTask::subtask",param_1), cVar2 == '\0'))
  {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ced10(param_2,param_1 + 0x34,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x40,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x44,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x48,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x4c,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ced10(param_2,param_1 + 0x50,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x5c,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ced10(param_2,param_1 + 0x60,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ceb10(param_2,param_1 + 0x18,4), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ced10(param_2,param_1 + 0x1c,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = 0;
  if ((bVar1) && (uVar3 = FUN_004ce910(param_2,param_1 + 0x28,4), (uVar3 & 0xff) != 0)) {
    local_40 = '\x01';
  }
  else {
    local_40 = '\0';
  }
  uVar3 = CONCAT31((int3)(uVar3 >> 8),local_40);
  if (local_40 != '\0') {
    uVar3 = FUN_00461c90(param_2);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      local_44 = 1;
      goto LAB_005b5ccc;
    }
  }
  local_44 = 0;
LAB_005b5ccc:
  return CONCAT31((int3)(uVar3 >> 8),local_44);
}

