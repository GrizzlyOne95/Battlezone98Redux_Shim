
undefined4 __thiscall FUN_005c33c0(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined1 local_40;
  char local_3c;
  char local_38;
  char local_34;
  char local_2c;
  char local_28;
  char local_24;
  char local_20;
  char local_1c;
  char local_18;
  int local_10;
  int local_c;
  char local_5;
  
  local_5 = 1;
  local_c = param_1;
  cVar1 = FUN_004ceb10(param_2,param_1 + 0x18,4);
  local_5 = cVar1 != '\0';
  if (((bool)local_5) && (cVar1 = FUN_004ce910(param_2,&local_10,4), cVar1 != '\0')) {
    local_18 = '\x01';
  }
  else {
    local_18 = '\0';
  }
  local_5 = local_18;
  if (local_10 != 0) {
    *(int *)(local_c + 0x1c) = local_10;
  }
  if ((local_18 == '\0') || (cVar1 = FUN_004ce910(param_2,&local_10,4), cVar1 == '\0')) {
    local_1c = '\0';
  }
  else {
    local_1c = '\x01';
  }
  local_5 = local_1c;
  if (local_10 != 0) {
    *(int *)(local_c + 0x20) = local_10;
  }
  if ((local_1c == '\0') || (cVar1 = FUN_004ce910(param_2,local_c + 0x24,4), cVar1 == '\0')) {
    local_20 = '\0';
  }
  else {
    local_20 = '\x01';
  }
  local_5 = local_20;
  if ((local_20 == '\0') ||
     (cVar1 = FUN_004cf640(param_2,local_c + 0x28,4,"ScavengerProcess::craft",local_c),
     cVar1 == '\0')) {
    local_24 = '\0';
  }
  else {
    local_24 = '\x01';
  }
  local_5 = local_24;
  if ((local_24 == '\0') || (cVar1 = FUN_004ced10(param_2,local_c + 0x2c,0xc), cVar1 == '\0')) {
    local_28 = '\0';
  }
  else {
    local_28 = '\x01';
  }
  local_5 = local_28;
  if ((local_28 == '\0') || (cVar1 = FUN_004ced10(param_2,local_c + 0x38,0xc), cVar1 == '\0')) {
    local_2c = '\0';
  }
  else {
    local_2c = '\x01';
  }
  local_5 = local_2c;
  if ((local_2c == '\0') || (cVar1 = FUN_004ceb10(param_2,local_c + 0x44,4), cVar1 == '\0')) {
    local_5 = false;
  }
  else {
    local_5 = true;
  }
  if (((bool)local_5) && (cVar1 = FUN_004ce5e0(param_2,local_c + 0x48,1), cVar1 != '\0')) {
    local_34 = '\x01';
  }
  else {
    local_34 = '\0';
  }
  uVar2 = 0;
  local_5 = local_34;
  if ((local_34 == '\0') || (uVar2 = FUN_004ce910(param_2,local_c + 0x4c,4), (uVar2 & 0xff) == 0)) {
    local_38 = '\0';
  }
  else {
    local_38 = '\x01';
  }
  uVar2 = CONCAT31((int3)(uVar2 >> 8),local_38);
  local_5 = local_38;
  if ((local_38 == '\0') ||
     (uVar2 = FUN_004cf640(param_2,local_c + 0x58,4,"ScavengerProcess::task",local_c),
     (uVar2 & 0xff) == 0)) {
    local_3c = '\0';
  }
  else {
    local_3c = '\x01';
  }
  uVar2 = CONCAT31((int3)(uVar2 >> 8),local_3c);
  local_5 = local_3c;
  if (local_3c != '\0') {
    uVar2 = FUN_004616d0(param_2);
    uVar2 = uVar2 & 0xff;
    if (uVar2 != 0) {
      local_40 = 1;
      goto LAB_005c36a0;
    }
  }
  local_40 = 0;
LAB_005c36a0:
  return CONCAT31((int3)(uVar2 >> 8),local_40);
}

