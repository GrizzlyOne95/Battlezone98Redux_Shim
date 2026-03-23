
undefined4 FUN_004cef70(undefined4 param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int local_18;
  int local_14;
  uint local_10;
  int local_c;
  undefined1 local_6;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,1,0xb,param_3);
    FUN_004ce0b0();
    iVar3 = sscanf(DAT_0260db08,"%*s [%d] =",&local_18);
    local_6 = iVar3 == 1;
    local_10 = (uint)(byte)local_6;
    FUN_004ce100();
    for (local_c = 0; local_c < local_18; local_c = local_c + 1) {
      cVar1 = FUN_004ceb10(param_1,local_c * 0x40 + param_2,4);
      if (((((cVar1 == '\0') ||
            (cVar1 = FUN_004ceb10(param_1,param_2 + 4 + local_c * 0x40,4), cVar1 == '\0')) ||
           (cVar1 = FUN_004ceb10(param_1,param_2 + 8 + local_c * 0x40,4), cVar1 == '\0')) ||
          ((((cVar1 = FUN_004ceb10(param_1,param_2 + 0xc + local_c * 0x40,4), cVar1 == '\0' ||
             (cVar1 = FUN_004ceb10(param_1,param_2 + 0x10 + local_c * 0x40,4), cVar1 == '\0')) ||
            ((cVar1 = FUN_004ceb10(param_1,param_2 + 0x14 + local_c * 0x40,4), cVar1 == '\0' ||
             ((cVar1 = FUN_004ceb10(param_1,param_2 + 0x18 + local_c * 0x40,4), cVar1 == '\0' ||
              (cVar1 = FUN_004ceb10(param_1,param_2 + 0x1c + local_c * 0x40,4), cVar1 == '\0'))))))
           || (cVar1 = FUN_004ceb10(param_1,param_2 + 0x20 + local_c * 0x40,4), cVar1 == '\0')))) ||
         (((cVar1 = FUN_004cec20(param_1,param_2 + 0x28 + local_c * 0x40,8), cVar1 == '\0' ||
           (cVar1 = FUN_004cec20(param_1,param_2 + 0x30 + local_c * 0x40,8), cVar1 == '\0')) ||
          (cVar1 = FUN_004cec20(param_1,param_2 + 0x38 + local_c * 0x40,8), cVar1 == '\0')))) {
        local_14 = 0;
      }
      else {
        local_14 = 1;
      }
      local_5 = (undefined1)local_14;
      if (local_14 == 0) {
        return 0;
      }
    }
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004cdda0(0xb,param_3,param_2);
  }
  return uVar2;
}

