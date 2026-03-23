
undefined4 * __thiscall
FUN_007c9a10(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e6c8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_007d1cc0(param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  local_8 = 0;
  *param_1 = cUI_ProgressBar::vftable;
  uVar2 = FUN_00822e60(uVar1);
  param_1[0x51] = uVar2;
  param_1[0x52] = 0;
  param_1[0x53] = param_5;
  FUN_007d2870("progress.png");
  FUN_007c9bb0(DAT_008f0688,0,0);
  DAT_009455ec = param_1;
  ExceptionList = local_10;
  return param_1;
}

