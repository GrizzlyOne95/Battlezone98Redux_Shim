
void __fastcall FUN_0041abe0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00844c03;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = TouchInputButton::vftable;
  local_8 = 1;
  if (param_1[0x25] != 0) {
    (**(code **)(*(int *)param_1[0x25] + 0x28))(param_1,uVar1);
  }
  local_8 = local_8 & 0xffffff00;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00418ef0();
  ExceptionList = local_10;
  return;
}

