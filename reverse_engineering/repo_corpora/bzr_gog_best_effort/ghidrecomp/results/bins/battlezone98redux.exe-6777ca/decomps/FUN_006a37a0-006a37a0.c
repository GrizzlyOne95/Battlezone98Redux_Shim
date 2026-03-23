
void FUN_006a37a0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084711c;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (DAT_00920c9b == '\0') {
    DAT_00920c9b = '\x01';
    pvVar2 = operator_new(0x24);
    local_8 = 0;
    if (pvVar2 != (void *)0x0) {
      uVar3 = FUN_0045ca50();
      FUN_006a2820(uVar3);
    }
  }
  local_8 = 0xffffffff;
  FUN_006902b0(param_1,param_2,uVar1);
  ExceptionList = local_10;
  return;
}

