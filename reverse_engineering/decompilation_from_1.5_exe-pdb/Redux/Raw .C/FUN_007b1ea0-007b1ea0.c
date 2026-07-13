
void __fastcall FUN_007b1ea0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00861048;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUI_OptionsGraphics::vftable;
  local_8 = 0;
  if (param_1[0x5e] != 0) {
    FUN_007d21c0(param_1[0x5e]);
    if ((undefined4 *)param_1[0x5e] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0x5e])(1);
    }
  }
  local_8 = 0xffffffff;
  FUN_007d1eb0(uVar1);
  ExceptionList = local_10;
  return;
}

