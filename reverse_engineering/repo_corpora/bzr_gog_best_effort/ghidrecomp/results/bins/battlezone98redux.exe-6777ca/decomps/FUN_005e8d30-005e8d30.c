
undefined1 __thiscall FUN_005e8d30(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 local_2c;
  int local_14;
  int local_10;
  
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ce5e0(param_2,param_1 + 0x54,0x18);
    if ((cVar2 == '\0') || (cVar2 = FUN_004ceb10(param_2,param_1 + 0x70,4), cVar2 == '\0')) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 4;
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0x78,0x10), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
      if ((bVar1) &&
         (cVar2 = FUN_004cf640(param_2,param_1 + 0x8c + local_14 * 4,4,"Tran03Mission::p_array",
                               param_1), cVar2 != '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    if ((bVar1) && (cVar2 = FUN_004ce910(param_2,param_1 + 0xa0,4,1,uVar3), cVar2 != '\0')) {
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
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      *(undefined4 *)(param_1 + 0x78 + local_10 * 4) = 0;
    }
    FUN_005e7fa0();
    local_2c = FUN_0045d570(param_2);
  }
  return local_2c;
}

