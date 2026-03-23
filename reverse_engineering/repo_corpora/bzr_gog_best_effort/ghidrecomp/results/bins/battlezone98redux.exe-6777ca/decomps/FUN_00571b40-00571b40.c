
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00571b40(undefined4 *param_1,undefined2 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_0073a9f0(local_2c);
  local_8 = 0;
  uVar2 = FUN_0041f870(uVar1,extraout_var,uVar2,uVar2);
  FUN_007d6a70("Net: Setting local user ID information to %u (remote %s)\n",param_2,uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>();
  _DAT_009c8f60 = *param_1;
  _DAT_009c8f64 = param_1[1];
  _DAT_009c8f68 = param_1[2];
  _DAT_009c8f6c = param_1[3];
  DAT_009180d4 = param_2;
  FUN_004b7930(param_2);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

