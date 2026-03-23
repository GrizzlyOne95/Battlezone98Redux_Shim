
undefined1 FUN_008037e0(void)

{
  char cVar1;
  undefined4 in_stack_0000003c;
  undefined1 auStack_64 [56];
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
  
  puStack_c = &LAB_00864618;
  local_10 = ExceptionList;
  uStack_24 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  puStack_28 = &stack0x00000004;
  uStack_2c = 0x803818;
  puStack_28 = (undefined1 *)FUN_0066eeb0();
  uStack_2c = 0x803821;
  cVar1 = FUN_006dc8e0();
  if (cVar1 == '\0') {
    local_11 = 0;
    puStack_28 = (undefined1 *)0x0;
    uStack_2c = in_stack_0000003c;
    local_1c = auStack_64;
    local_20 = FUN_007fc680(&stack0x00000004);
    FUN_00804730();
    local_12 = 1;
    local_8 = 0xffffffff;
    puStack_28 = (undefined1 *)0x803868;
    CTraceSnapshot::~CTraceSnapshot((CTraceSnapshot *)&stack0x00000004);
  }
  else {
    local_13 = 0;
    local_8 = 0xffffffff;
    puStack_28 = (undefined1 *)0x803882;
    CTraceSnapshot::~CTraceSnapshot((CTraceSnapshot *)&stack0x00000004);
    local_12 = local_13;
  }
  ExceptionList = local_10;
  return local_12;
}

