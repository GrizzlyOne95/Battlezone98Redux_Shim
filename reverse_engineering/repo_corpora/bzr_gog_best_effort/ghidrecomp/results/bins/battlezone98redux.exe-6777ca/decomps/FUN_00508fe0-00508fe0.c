
void __fastcall FUN_00508fe0(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084aae3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = LuaMission::vftable;
  param_1[0x15] = LuaMission::vftable;
  local_8 = 1;
  iVar2 = FUN_007659f0(uVar1);
  if (iVar2 != 0) {
    if (param_1 == (undefined4 *)0x0) {
      local_18 = (undefined4 *)0x0;
    }
    else {
      local_18 = param_1 + 0x15;
    }
    FUN_00758b20(0x23,local_18);
  }
  if (param_1[0x16] != 0) {
    FUN_0082d6fd(param_1[0x16]);
  }
  local_8 = local_8 & 0xffffff00;
  FUN_00758a30();
  local_8 = 0xffffffff;
  FUN_0045cb70();
  ExceptionList = local_10;
  return;
}

