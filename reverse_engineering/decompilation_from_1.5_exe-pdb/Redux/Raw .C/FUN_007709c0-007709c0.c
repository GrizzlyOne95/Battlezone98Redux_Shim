
void FUN_007709c0(void)

{
  byte in_stack_0000001c;
  undefined4 uStack_58;
  undefined1 *puStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined1 *puStack_44;
  uint uStack_40;
  uint uStack_3c;
  undefined1 local_38 [8];
  undefined1 local_30 [8];
  undefined4 local_28;
  undefined1 *local_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined4 *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0085df40;
  local_10 = ExceptionList;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 1;
  uStack_40 = (uint)in_stack_0000001c;
  puStack_44 = &stack0x00000004;
  uStack_48 = 0x7709fd;
  puStack_44 = (undefined1 *)FUN_00732e10();
  local_1c = (undefined1 *)&uStack_50;
  puStack_54 = &stack0x00000010;
  uStack_58 = 0x770a0f;
  local_20 = FUN_004bbb20();
  puStack_54 = local_30;
  uStack_58 = 0x770a1b;
  local_14 = (undefined4 *)FUN_0072f070();
  uStack_48 = local_14[1];
  uStack_4c = *local_14;
  local_24 = (undefined1 *)&uStack_58;
  local_28 = FUN_004bbb20(&stack0x00000004);
  local_18 = (undefined4 *)FUN_0072f070(local_38);
  uStack_50 = local_18[1];
  puStack_54 = (undefined1 *)*local_18;
  uStack_58 = 0x770a5d;
  FUN_00770ee0();
  local_8 = local_8 & 0xffffff00;
  uStack_40 = 0x770a6c;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  uStack_40 = 0x770a7b;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return;
}

