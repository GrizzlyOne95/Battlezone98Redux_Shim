
void FUN_007ea220(void)

{
  void *pvVar1;
  undefined4 *in_stack_0000002c;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845f6c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x28);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_007dd690(&stack0x00000004);
  }
  *in_stack_0000002c = local_18;
  ExceptionList = local_10;
  return;
}

