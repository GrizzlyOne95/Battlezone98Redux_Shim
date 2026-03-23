
undefined1 FUN_004cf7b0(undefined4 param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  undefined1 local_5;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,8,param_3);
    FUN_004ce0b0();
    iVar1 = sscanf(DAT_0260db08,"%*s = %p",param_2);
    local_5 = iVar1 == 1;
    local_c = (uint)(byte)local_5;
    FUN_004ce100();
  }
  else if (DAT_00917b20 < 0x7dc) {
    local_5 = FUN_004cdda0(8,4,&local_10);
    *param_2 = local_10;
  }
  else {
    local_5 = FUN_004cdda0(8,8,&local_18);
    *param_2 = local_18;
    if ((local_18 != *param_2) || (local_14 != 0)) {
      local_5 = 0;
    }
  }
  return local_5;
}

