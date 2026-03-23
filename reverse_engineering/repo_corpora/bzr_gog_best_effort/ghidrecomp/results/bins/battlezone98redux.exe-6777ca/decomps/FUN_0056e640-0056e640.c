
void __fastcall FUN_0056e640(undefined4 *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 *local_18;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_0084b4c3;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = MultGMission::vftable;
  param_1[0x15] = MultGMission::vftable;
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
  local_8 = local_8 & 0xffffff00;
  FUN_00758a10();
  local_8 = 0xffffffff;
  FUN_0045cb70();
  ExceptionList = local_10;
  return;
}

