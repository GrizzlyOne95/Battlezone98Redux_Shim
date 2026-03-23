
void __fastcall FUN_00457170(undefined4 *param_1)

{
  uint uVar1;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00846618;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = TrailRender::vftable;
  local_8 = 0;
  if (param_1[0x1c] != 0) {
    for (local_18 = 0; local_18 < (uint)param_1[0x1d]; local_18 = local_18 + 1) {
      FUN_00456f20(*(undefined4 *)(param_1[0x1c] + local_18 * 4));
    }
    param_1[0x1d] = 0;
    operator_delete__((void *)param_1[0x1c]);
    param_1[0x1c] = 0;
  }
  local_8 = 0xffffffff;
  FUN_00448f70(uVar1);
  ExceptionList = local_10;
  return;
}

