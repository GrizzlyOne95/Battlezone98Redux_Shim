
undefined4 __thiscall FUN_00512cc0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined1 local_30;
  char local_2c;
  
  cVar2 = FUN_004cd1b0(param_2,param_1 + 0x150,4,"mineCount");
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cd360(param_2,param_1 + 0x154,4,"radiusInc"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x158,4,"angleDec"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x15c,4,&DAT_0087d774), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x160,4,"radius"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x164,4,"angle"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004cd360(param_2,param_1 + 0x168,4,"angleInc"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = 0;
  if ((bVar1) && (uVar3 = FUN_004cd520(param_2,param_1 + 0x16c,0xc,"center"), (uVar3 & 0xff) != 0))
  {
    local_2c = '\x01';
  }
  else {
    local_2c = '\0';
  }
  uVar3 = CONCAT31((int3)(uVar3 >> 8),local_2c);
  if (local_2c != '\0') {
    uVar3 = FUN_004e7460(param_2);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      local_30 = 1;
      goto LAB_00512f05;
    }
  }
  local_30 = 0;
LAB_00512f05:
  return CONCAT31((int3)(uVar3 >> 8),local_30);
}

