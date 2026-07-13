
undefined1 __thiscall FUN_00528af0(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 local_2c;
  int local_14;
  int local_10;
  
  FUN_005c9470(1,3);
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x12a);
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x180,0x74), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 200;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x1f8,800), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    for (local_14 = 0; local_14 < 0x70; local_14 = local_14 + 1) {
      if ((bVar1) &&
         (cVar2 = FUN_004cf640(param_2,param_1 + 0x51c + local_14 * 4,4,"Misn07Mission::p_array",
                               param_1), cVar2 != '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x6e0,0x14,5,uVar3), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_0045d570(param_2), cVar2 != '\0')) {
      local_2c = 1;
    }
    else {
      local_2c = 0;
    }
  }
  else {
    for (local_10 = 0; local_10 < 0x12a; local_10 = local_10 + 1) {
      *(undefined1 *)(param_1 + local_10 + 0x54) = 0;
    }
    for (local_10 = 0; local_10 < 0x1d; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x180 + local_10 * 4) = 0x47c34f80;
    }
    for (local_10 = 0; local_10 < 200; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x1f8 + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 0x70; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x51c + local_10 * 4) = 0;
    }
    for (local_10 = 0; local_10 < 5; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x6e0 + local_10 * 4) = 0;
    }
    FUN_005291d0();
    local_2c = FUN_0045d570(param_2);
  }
  return local_2c;
}

