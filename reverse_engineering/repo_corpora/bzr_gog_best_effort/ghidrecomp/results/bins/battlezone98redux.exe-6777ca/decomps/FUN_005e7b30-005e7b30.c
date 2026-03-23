
undefined1 __thiscall FUN_005e7b30(int param_1,undefined4 param_2)

{
  bool bVar1;
  char cVar2;
  undefined4 uVar3;
  undefined1 local_28;
  int local_10;
  
  if (DAT_009173b7 == '\0') {
    cVar2 = FUN_004ccf20(param_2,param_1 + 0x54,0x16,"b_array");
    if ((cVar2 == '\0') || (cVar2 = FUN_004cd360(param_2,param_1 + 0x6c,8,"f_array"), cVar2 == '\0')
       ) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    uVar3 = 4;
    if ((bVar1) && (cVar2 = FUN_004cd1b0(param_2,param_1 + 0x78,0x10,"h_array"), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      if ((bVar1) &&
         (cVar2 = FUN_004cf520(param_2,param_1 + 0x8c + local_10 * 4,4,"p_array"), cVar2 != '\0')) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
    }
    if ((bVar1) &&
       (cVar2 = FUN_004cd1b0(param_2,param_1 + 0xa0,0xc,"i_array",3,uVar3), cVar2 != '\0')) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if ((bVar1) && (cVar2 = FUN_0045d830(param_2), cVar2 != '\0')) {
      local_28 = 1;
    }
    else {
      local_28 = 0;
    }
  }
  else {
    local_28 = FUN_0045d830(param_2);
  }
  return local_28;
}

