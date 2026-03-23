
void FUN_006a9970(void)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fd7b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  piVar1 = (int *)FUN_006a9180();
  (**(code **)(*piVar1 + 0x28))();
  FUN_006a9a65();
  return;
}

