
undefined4 FUN_004cec20(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  int local_18;
  uint local_14;
  uint local_10;
  int local_c;
  undefined1 local_6;
  char local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,6,param_3);
    FUN_004ce0b0();
    iVar2 = sscanf(DAT_0260db08,"%*s [%d] =",&local_18);
    local_6 = iVar2 == 1;
    local_10 = (uint)(byte)local_6;
    FUN_004ce100();
    for (local_c = 0; local_c < local_18; local_c = local_c + 1) {
      FUN_004ce0b0();
      iVar2 = sscanf(DAT_0260db08,"%lg",param_2 + local_c * 8);
      local_5 = iVar2 == 1;
      local_14 = (uint)(byte)local_5;
      FUN_004ce100();
      if (local_5 == '\0') {
        return 0;
      }
    }
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004cdda0(6,param_3,param_2);
  }
  return uVar1;
}

