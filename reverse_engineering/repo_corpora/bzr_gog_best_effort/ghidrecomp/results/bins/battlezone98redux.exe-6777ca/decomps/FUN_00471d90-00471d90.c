
undefined4 FUN_00471d90(void)

{
  uint uVar1;
  void *pvVar2;
  undefined4 local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084711c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pvVar2 = operator_new(0x134);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_18 = 0;
  }
  else {
    local_18 = FUN_00471500(uVar1);
  }
  ExceptionList = local_10;
  return local_18;
}

