
undefined4 __thiscall FUN_0059c960(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  uint uVar3;
  undefined1 local_1c;
  char local_18;
  
  cVar2 = FUN_004ce910(param_2,param_1 + 0x14c,4);
  if ((cVar2 == '\0') ||
     (cVar2 = FUN_004cf640(param_2,param_1 + 0x150,4,"PatrolTask::my_craft",param_1), cVar2 == '\0')
     ) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  uVar3 = 0;
  if ((bVar1) && (uVar3 = FUN_004ce910(param_2,param_1 + 0x154,4), (uVar3 & 0xff) != 0)) {
    local_18 = '\x01';
  }
  else {
    local_18 = '\0';
  }
  uVar3 = CONCAT31((int3)(uVar3 >> 8),local_18);
  if (local_18 != '\0') {
    uVar3 = FUN_004e5b10(param_2);
    uVar3 = uVar3 & 0xff;
    if (uVar3 != 0) {
      local_1c = 1;
      goto LAB_0059ca57;
    }
  }
  local_1c = 0;
LAB_0059ca57:
  return CONCAT31((int3)(uVar3 >> 8),local_1c);
}

