
void __fastcall FUN_005703a0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084b708;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = Net::vftable;
  local_8 = 0;
  FUN_007659f0(param_1,uVar1);
  FUN_00758ac0(param_1);
  FUN_00570460();
  FUN_006246d0();
  FUN_007a47b0(0,0);
  FUN_0046ce20();
  FUN_00627e10();
  FUN_005767b0();
  FUN_004b8f50();
  DAT_00917f78 = 0;
  DAT_00917f7b = 0;
  local_8 = 0xffffffff;
  FUN_00758a30();
  ExceptionList = local_10;
  return;
}

