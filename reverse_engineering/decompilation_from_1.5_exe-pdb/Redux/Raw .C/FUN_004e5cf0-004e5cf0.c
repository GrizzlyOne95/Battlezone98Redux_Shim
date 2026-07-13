
undefined4 __thiscall FUN_004e5cf0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined1 local_24;
  char local_20;
  
  cVar2 = FUN_004cf520(param_2,param_1 + 0x134,4,&DAT_0087a548);
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x138,4,"pathPoint"), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 0x13c,1,"release"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  if ((bVar1) && (cVar2 = FUN_004ccf20(param_2,param_1 + 0x13d,1,"exact"), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar3 = 0;
  if ((bVar1) &&
     (uVar3 = FUN_004cd520(param_2,param_1 + 0x140,0xc,"destPoint"), (uVar3 & 0xff) != 0)) {
    local_20 = '\x01';
  }
  else {
    local_20 = '\0';
  }
  uVar3 = CONCAT31((int3)(uVar3 >> 8),local_20);
  if (local_20 != '\0') {
    uVar3 = FUN_005ffa70(param_2);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      local_24 = 1;
      goto LAB_004e5e70;
    }
  }
  local_24 = 0;
LAB_004e5e70:
  return CONCAT31((int3)(uVar3 >> 8),local_24);
}

