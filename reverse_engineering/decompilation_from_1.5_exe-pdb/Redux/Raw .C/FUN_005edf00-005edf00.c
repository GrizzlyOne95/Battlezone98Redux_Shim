
undefined4 __thiscall FUN_005edf00(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined1 local_30;
  char local_2c;
  
  cVar2 = FUN_004cd1b0(param_2,param_1 + 0x18,4,"curState");
  if ((cVar2 == '\0') || (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x1c,4,"nextState"), cVar2 == '\0')
     ) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cf520(param_2,param_1 + 0x20,4,"craft"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd520(param_2,param_1 + 0x24,0xc,"where"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x30,4,"whoHandle"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cf520(param_2,param_1 + 0x34,4,&DAT_00875dcc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x38,4,"dropoffPoint"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = 0;
  if ((bVar1) &&
     (uVar3 = FUN_004cd520(param_2,param_1 + 0x3c,0xc,"tugLocation"), (uVar3 & 0xff) != 0)) {
    local_2c = '\x01';
  }
  else {
    local_2c = '\0';
  }
  uVar3 = CONCAT31((int3)(uVar3 >> 8),local_2c);
  if (local_2c != '\0') {
    uVar3 = FUN_004617b0(param_2);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      local_30 = 1;
      goto LAB_005ee130;
    }
  }
  local_30 = 0;
LAB_005ee130:
  return CONCAT31((int3)(uVar3 >> 8),local_30);
}

