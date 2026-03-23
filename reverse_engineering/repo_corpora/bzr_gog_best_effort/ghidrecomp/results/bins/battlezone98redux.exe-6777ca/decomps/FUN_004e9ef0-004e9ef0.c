
void __fastcall FUN_004e9ef0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084a598;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = HoverCraft::vftable;
  param_1[6] = HoverCraft::vftable;
  local_8 = 0;
  if (param_1[0xaa] != 0) {
    if ((undefined4 *)param_1[0xaa] != (undefined4 *)0x0) {
      (*(code *)**(undefined4 **)param_1[0xaa])(1,uVar1);
    }
    param_1[0xaa] = 0;
  }
  local_8 = 0xffffffff;
  FUN_004a7ea0();
  ExceptionList = local_10;
  return;
}

