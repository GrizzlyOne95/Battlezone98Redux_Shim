
void __fastcall FUN_005d8950(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008494a8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = SpawnBuoy::vftable;
  param_1[6] = SpawnBuoy::vftable;
  local_8 = 0;
  if ((param_1[0x8e] != 0) && (param_1[0x8e] != 0)) {
    FUN_005d89f0(1);
  }
  local_8 = 0xffffffff;
  FUN_0047eab0(uVar1);
  ExceptionList = local_10;
  return;
}

