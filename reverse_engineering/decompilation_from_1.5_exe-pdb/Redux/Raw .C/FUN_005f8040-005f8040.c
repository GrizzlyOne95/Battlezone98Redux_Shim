
undefined4 __thiscall FUN_005f8040(int param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined1 local_18;
  char local_14;
  
  cVar1 = FUN_004ceb10(param_2,param_1 + 0x134,4);
  uVar2 = 0;
  if ((cVar1 == '\0') || (uVar2 = FUN_004ceb10(param_2,param_1 + 0x138,4), (uVar2 & 0xff) == 0)) {
    local_14 = '\0';
  }
  else {
    local_14 = '\x01';
  }
  uVar2 = CONCAT31((int3)(uVar2 >> 8),local_14);
  if (local_14 != '\0') {
    uVar2 = FUN_005fef80(param_2);
    uVar2 = uVar2 & 0xff;
    if (uVar2 != 0) {
      local_18 = 1;
      goto LAB_005f80f1;
    }
  }
  local_18 = 0;
LAB_005f80f1:
  return CONCAT31((int3)(uVar2 >> 8),local_18);
}

