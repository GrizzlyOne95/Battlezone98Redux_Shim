
undefined4 __fastcall FUN_00705380(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00856e68;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_006d1110(param_1 + 0xc);
  local_8 = 0;
  uVar2 = FUN_0070f840(param_1);
  local_8 = 0xffffffff;
  FUN_006d1140(uVar1);
  ExceptionList = local_10;
  return uVar2;
}

