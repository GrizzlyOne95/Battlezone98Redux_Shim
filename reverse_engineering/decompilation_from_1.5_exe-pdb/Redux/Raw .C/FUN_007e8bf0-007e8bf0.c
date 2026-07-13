
undefined1 FUN_007e8bf0(void)

{
  char cVar1;
  undefined4 in_stack_00000080;
  undefined1 auStack_a8 [124];
  undefined4 uStack_2c;
  undefined1 *puStack_28;
  uint uStack_24;
  undefined4 local_20;
  undefined1 *local_1c;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008635c8;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_28 = &stack0x00000004;
  uStack_2c = 0x7e8c28;
  puStack_28 = (undefined1 *)FUN_0066eeb0();
  uStack_2c = 0x7e8c31;
  cVar1 = FUN_006dc8e0();
  if (cVar1 == '\0') {
    local_11 = 0;
    puStack_28 = (undefined1 *)0x0;
    uStack_2c = in_stack_00000080;
    local_1c = auStack_a8;
    local_20 = FUN_007dd770(&stack0x00000004);
    FUN_007ea340();
    local_12 = 1;
    local_8 = 0xffffffff;
    puStack_28 = (undefined1 *)0x7e8c7b;
    FUN_007dba50();
  }
  else {
    local_13 = 0;
    local_8 = 0xffffffff;
    puStack_28 = (undefined1 *)0x7e8c95;
    FUN_007dba50();
    local_12 = local_13;
  }
  ExceptionList = local_10;
  return local_12;
}

