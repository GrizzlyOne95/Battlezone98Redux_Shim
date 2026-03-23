
void __fastcall FUN_005d7a70(int param_1)

{
  void *pvVar1;
  undefined4 local_20;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c57c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x3c) == 0) {
    local_18 = FUN_004b0400(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  }
  else {
    local_18 = FUN_00462630(*(undefined4 *)(param_1 + 0x3c));
  }
  pvVar1 = operator_new(0x14c);
  local_8 = 0;
  if (pvVar1 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = FUN_005d85d0(*(undefined4 *)(param_1 + 0x34),local_18);
  }
  *(undefined4 *)(param_1 + 0x38) = local_20;
  ExceptionList = local_10;
  return;
}

