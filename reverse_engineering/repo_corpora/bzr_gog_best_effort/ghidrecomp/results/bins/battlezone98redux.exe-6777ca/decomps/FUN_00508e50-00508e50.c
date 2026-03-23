
undefined4 * __fastcall FUN_00508e50(undefined4 *param_1)

{
  int iVar1;
  undefined4 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084aae3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0045ca60(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_00508f40();
  local_8 = CONCAT31(local_8._1_3_,1);
  *param_1 = LuaMission::vftable;
  param_1[0x15] = LuaMission::vftable;
  param_1[0x16] = 0;
  *(undefined1 *)(param_1 + 0x17) = 0;
  FUN_005090a0();
  iVar1 = FUN_007659f0();
  if (iVar1 != 0) {
    if (param_1 == (undefined4 *)0x0) {
      local_18 = (undefined4 *)0x0;
    }
    else {
      local_18 = param_1 + 0x15;
    }
    FUN_00758af0(0x23,local_18);
  }
  ExceptionList = local_10;
  return param_1;
}

