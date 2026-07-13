
undefined4 __thiscall FUN_00513070(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined1 local_28;
  char local_24;
  uint local_10;
  
  if (DAT_009173b7 != '\0') {
    FUN_00513550();
    uVar3 = FUN_0045d570(param_2);
    return uVar3;
  }
  cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x10);
  if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x68,0xc), cVar2 == '\0')) {
    bVar1 = false;
  }
  else {
    bVar1 = true;
  }
  if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x78,0xc), cVar2 != '\0')) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  uVar4 = param_1 + 0x88;
  iVar5 = (param_1 + 0x98) - uVar4;
  for (local_10 = 0; local_10 < (uint)(iVar5 >> 2); local_10 = local_10 + 1) {
    if ((bVar1) &&
       (cVar2 = FUN_004cf640(param_2,param_1 + 0x88 + local_10 * 4,4,"Misn01Mission::p_array",
                             param_1), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    uVar4 = 0;
  }
  if ((bVar1) && (uVar4 = FUN_004ce910(param_2,param_1 + 0x9c,0xc), (uVar4 & 0xff) != 0)) {
    local_24 = '\x01';
  }
  else {
    local_24 = '\0';
  }
  uVar4 = CONCAT31((int3)(uVar4 >> 8),local_24);
  if (local_24 != '\0') {
    uVar4 = FUN_0045d570(param_2);
    uVar4 = uVar4 & 0xff;
    if (uVar4 != 0) {
      local_28 = 1;
      goto LAB_00513235;
    }
  }
  local_28 = 0;
LAB_00513235:
  return CONCAT31((int3)(uVar4 >> 8),local_28);
}

