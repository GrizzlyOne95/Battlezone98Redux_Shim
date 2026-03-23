
undefined4 * __thiscall FUN_00458ad0(undefined4 *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846040;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00448f90(param_2,param_3);
  local_8 = 0;
  *param_1 = TwirlRenderClass::vftable;
  if (param_2 == 0) {
    param_1[0x5f] = 0;
    *(undefined1 *)(param_1 + 0x60) = 0;
  }
  else {
    uVar2 = FUN_00446460(param_1 + 0x15,0x811c9dc5,uVar1);
    FUN_00589430(param_1 + 0x25);
    local_8._0_1_ = 1;
    FUN_00589800(uVar2,0xe6989765,param_1 + 0x5f,*(undefined4 *)(param_2 + 0x17c));
    FUN_00589920(uVar2,0x876e1b38,param_1 + 0x60,*(undefined1 *)(param_2 + 0x180));
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00589530();
  }
  ExceptionList = local_10;
  return param_1;
}

