
int FUN_005d2970(int param_1,int param_2)

{
  int *piVar1;
  void *pvVar2;
  int local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084762c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  piVar1 = (int *)(DAT_009182d8 + (param_2 * DAT_009182dc + param_1) * 4);
  if (*piVar1 == 0) {
    pvVar2 = operator_new(0x28);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_005d28b0(param_1,param_2);
    }
    *piVar1 = local_1c;
  }
  ExceptionList = local_10;
  return *piVar1;
}

