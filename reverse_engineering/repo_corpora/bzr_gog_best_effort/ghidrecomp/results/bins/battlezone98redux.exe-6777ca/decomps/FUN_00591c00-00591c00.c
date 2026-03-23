
void FUN_00591c00(void)

{
  uint uVar1;
  void *pvVar2;
  undefined4 local_20;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084bf88;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pvVar2 = operator_new(0xc);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = vector<>(uVar1);
  }
  local_8 = 0xffffffff;
  DAT_02a13c8c = local_18;
  FUN_004bae50(0x80000);
  pvVar2 = operator_new(0xc);
  local_8 = 1;
  if (pvVar2 == (void *)0x0) {
    local_20 = 0;
  }
  else {
    local_20 = vector<>(uVar1);
  }
  local_8 = 0xffffffff;
  DAT_02a13ca4 = local_20;
  FUN_004bae50(0x80000);
  DAT_00918168 = 0;
  FUN_0046aac0();
  DAT_00918134 = 0x400;
  ExceptionList = local_10;
  return;
}

