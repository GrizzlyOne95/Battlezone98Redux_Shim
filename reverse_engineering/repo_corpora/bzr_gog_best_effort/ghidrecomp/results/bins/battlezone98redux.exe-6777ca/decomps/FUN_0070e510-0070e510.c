
void __thiscall FUN_0070e510(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_b4 [56];
  undefined4 uStack_7c;
  undefined4 uStack_78;
  uint uStack_74;
  undefined1 *local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  int local_60;
  undefined1 local_5c [72];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00857868;
  local_10 = ExceptionList;
  uStack_74 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_78 = param_3;
  uStack_7c = param_2;
  local_70 = auStack_b4;
  local_60 = param_1;
  local_14 = uStack_74;
  local_6c = <>(param_1 + 8);
  uStack_78 = FUN_00718ef0(local_5c);
  local_8 = 0;
  uStack_7c = 0x70e582;
  local_68 = uStack_78;
  local_64 = uStack_78;
  FUN_00718f60();
  local_8 = 0xffffffff;
  uStack_78 = 0x70e591;
  FUN_006ff950();
  ExceptionList = local_10;
  uStack_74 = 0x70e5a6;
  FUN_0083e885();
  return;
}

