
void __fastcall FUN_00512230(int param_1)

{
  void *pvVar1;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845f6c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  pvVar1 = operator_new(0x178);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_005124f0(*(undefined4 *)(param_1 + 0x34));
  }
  *(undefined4 *)(param_1 + 0x38) = local_18;
  ExceptionList = local_10;
  return;
}

