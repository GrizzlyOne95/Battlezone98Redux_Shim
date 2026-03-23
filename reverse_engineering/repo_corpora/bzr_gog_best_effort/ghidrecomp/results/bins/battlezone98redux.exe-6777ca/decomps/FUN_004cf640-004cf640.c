
undefined1
FUN_004cf640(undefined4 param_1,int *param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  int iVar1;
  int local_34;
  int local_30;
  int local_28 [2];
  int local_20;
  void *local_1c;
  uint local_18;
  char local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849f4c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(1,0,8,param_3,DAT_008e7000 ^ (uint)&stack0xfffffffc);
    FUN_004ce0b0();
    iVar1 = sscanf(DAT_0260db08,"%*s = %p",param_2);
    local_11 = iVar1 == 1;
    local_18 = (uint)(byte)local_11;
    FUN_004ce100();
  }
  else if (DAT_00917b20 < 0x7dc) {
    local_11 = FUN_004cdda0(8,4,local_28);
    *param_2 = local_28[0];
  }
  else {
    local_11 = FUN_004cdda0(8,8,&local_34);
    *param_2 = local_34;
    if ((local_34 != *param_2) || (local_30 != 0)) {
      ExceptionList = local_10;
      return 0;
    }
  }
  if (local_11 != '\0') {
    local_1c = operator_new(0x10);
    local_8 = 0;
    if (local_1c == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_004cc620(param_2,*param_2,param_4,param_5);
    }
    if (local_20 != 0) {
      ExceptionList = local_10;
      return 1;
    }
  }
  ExceptionList = local_10;
  return 0;
}

