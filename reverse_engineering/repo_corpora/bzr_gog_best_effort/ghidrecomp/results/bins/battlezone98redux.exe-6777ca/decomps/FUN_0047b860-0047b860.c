
void __fastcall FUN_0047b860(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00847938;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = BeamGun::vftable;
  local_8 = 0;
  if (param_1[0x34] != 0) {
    if (*(int *)(*(int *)(param_1[0x34] + 0xc) + 0xc) == 0x4245414d) {
      FUN_0047b760(uVar1);
    }
    param_1[0x34] = 0;
  }
  local_8 = 0xffffffff;
  FUN_00611500();
  ExceptionList = local_10;
  return;
}

