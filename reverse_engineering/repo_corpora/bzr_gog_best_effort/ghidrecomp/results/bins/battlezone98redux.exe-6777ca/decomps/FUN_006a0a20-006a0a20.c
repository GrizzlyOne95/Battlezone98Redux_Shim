
int FUN_006a0a20(undefined4 param_1)

{
  int *piVar1;
  void *pvVar2;
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  piVar1 = (int *)FUN_004200d0(DAT_02c00ec0);
  local_1c = *piVar1;
  if (local_1c == 0) {
    pvVar2 = operator_new(0x8c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_006a0ae0(param_1);
    }
    local_8 = 0xffffffff;
    piVar1 = (int *)FUN_004200d0(DAT_02c00ec0);
    *piVar1 = local_1c;
  }
  ExceptionList = local_10;
  return local_1c + 4;
}

