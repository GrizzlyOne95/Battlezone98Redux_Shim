
void __fastcall FUN_007c26e0(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00861e24;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_Button::vftable;
  local_8 = 2;
  if ((undefined4 *)param_1[0x51] == (undefined4 *)0x0) {
    uVar2 = 0;
  }
  else {
    uVar2 = (*(code *)**(undefined4 **)param_1[0x51])(1,uVar1);
  }
  local_8._0_1_ = 1;
  FUN_004499a0(uVar1,uVar2);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004499a0();
  local_8 = 0xffffffff;
  FUN_007d1eb0();
  ExceptionList = local_10;
  return;
}

