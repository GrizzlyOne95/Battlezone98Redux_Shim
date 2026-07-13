
int __fastcall FUN_00802510(int param_1)

{
  void *pvVar1;
  int local_24;
  int local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084641c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x68);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = clone_impl<>(param_1 + -100,0,1);
  }
  if (local_20 == 0) {
    local_24 = 0;
  }
  else {
    local_24 = local_20 + 0x5c + *(int *)(*(int *)(local_20 + 0x5c) + 4);
  }
  ExceptionList = local_10;
  return local_24;
}

