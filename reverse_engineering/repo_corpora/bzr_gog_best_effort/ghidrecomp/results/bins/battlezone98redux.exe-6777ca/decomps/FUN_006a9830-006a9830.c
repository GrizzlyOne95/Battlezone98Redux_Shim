
void FUN_006a9830(void)

{
  int *piVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084fd43;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 1;
  piVar1 = (int *)FUN_006a9180();
  uVar2 = FUN_0041f870();
  (**(code **)(*piVar1 + 0x20))(uVar2);
  FUN_006a9932();
  return;
}

