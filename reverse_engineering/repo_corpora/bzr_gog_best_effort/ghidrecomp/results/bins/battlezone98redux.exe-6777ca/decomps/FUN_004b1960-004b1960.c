
undefined1 __thiscall FUN_004b1960(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 local_28;
  int local_10;
  
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x13);
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x68,0x14), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 0x11;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x84,0x30), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      if ((bVar1) &&
         (cVar2 = FUN_004cf640(param_2,param_1 + 0xcc + local_10 * 4,4,"DemoMission::p_array",
                               param_1), cVar2 != '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0xe0,0x14,6,uVar3), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_0045d570(param_2), cVar2 != '\0')) {
      local_28 = 1;
    }
    else {
      local_28 = 0;
    }
  }
  else {
    FUN_004b1ec0();
    local_28 = FUN_0045d570(param_2);
  }
  return local_28;
}

