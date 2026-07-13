
void FUN_00804730(void)

{
  void *pvVar1;
  undefined4 *in_stack_0000003c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00864894;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  pvVar1 = operator_new(0x38);
  local_8 = CONCAT31(local_8._1_3_,1);
  if (pvVar1 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_007fc680(&stack0x00000004);
  }
  *in_stack_0000003c = local_18;
  local_8 = 0xffffffff;
  CTraceSnapshot::~CTraceSnapshot((CTraceSnapshot *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

