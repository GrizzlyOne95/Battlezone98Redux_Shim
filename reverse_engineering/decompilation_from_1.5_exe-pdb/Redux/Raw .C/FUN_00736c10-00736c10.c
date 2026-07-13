
void __thiscall FUN_00736c10(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_cc [64];
  undefined4 uStack_8c;
  undefined4 uStack_88;
  uint uStack_84;
  undefined1 *local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  int local_70;
  CAtlBaseModule local_6c [88];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00854da8;
  local_10 = ExceptionList;
  uStack_84 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_88 = param_3;
  uStack_8c = param_2;
  local_80 = auStack_cc;
  local_70 = param_1;
  local_14 = uStack_84;
  local_7c = FUN_0071e5c0(param_1 + 8);
  uStack_88 = FUN_00737840(local_6c);
  local_8 = 0;
  uStack_8c = 0x736c82;
  local_78 = uStack_88;
  local_74 = uStack_88;
  FUN_007378b0();
  local_8 = 0xffffffff;
  uStack_88 = 0x736c91;
  ATL::CAtlBaseModule::~CAtlBaseModule(local_6c);
  ExceptionList = local_10;
  uStack_84 = 0x736ca6;
  FUN_0083e885();
  return;
}

