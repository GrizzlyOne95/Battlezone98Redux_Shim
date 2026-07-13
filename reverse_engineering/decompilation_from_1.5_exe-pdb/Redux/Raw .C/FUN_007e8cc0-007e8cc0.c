
undefined1 FUN_007e8cc0(void)

{
  char cVar1;
  undefined4 in_stack_00000030;
  undefined1 auStack_58 [44];
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
  
  puStack_c = &LAB_008635f8;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_28 = &stack0x00000004;
  uStack_2c = 0x7e8cf8;
  puStack_28 = (undefined1 *)FUN_0066eeb0();
  uStack_2c = 0x7e8d01;
  cVar1 = FUN_006dc8e0();
  if (cVar1 == '\0') {
    local_11 = 0;
    puStack_28 = (undefined1 *)0x0;
    uStack_2c = in_stack_00000030;
    local_1c = auStack_58;
    local_20 = FUN_007dd790(&stack0x00000004);
    FUN_007ea3e0();
    local_12 = 1;
    local_8 = 0xffffffff;
    puStack_28 = (undefined1 *)0x7e8d48;
    FUN_007dba90();
  }
  else {
    local_13 = 0;
    local_8 = 0xffffffff;
    puStack_28 = (undefined1 *)0x7e8d62;
    FUN_007dba90();
    local_12 = local_13;
  }
  ExceptionList = local_10;
  return local_12;
}

