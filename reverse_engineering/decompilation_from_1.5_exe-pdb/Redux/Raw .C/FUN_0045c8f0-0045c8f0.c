
void FUN_0045c8f0(void)

{
  void *pvVar1;
  int local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084711c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (DAT_00917378 == 0) {
    pvVar1 = operator_new(8);
    local_8 = 0;
    if (pvVar1 == (void *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = vector<>();
    }
    DAT_00917378 = local_18;
  }
  local_8 = 0xffffffff;
  FUN_00438be0(&stack0x00000004);
  ExceptionList = local_10;
  return;
}

