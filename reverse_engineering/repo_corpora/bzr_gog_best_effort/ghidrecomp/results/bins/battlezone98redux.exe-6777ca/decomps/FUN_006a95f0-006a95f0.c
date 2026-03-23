
void FUN_006a95f0(void)

{
  int *piVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fcdb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  piVar1 = (int *)FUN_006a9180();
  FUN_006a9140();
  (**(code **)(*piVar1 + 4))();
  FUN_006a96de();
  return;
}

