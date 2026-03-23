
void FUN_00772a00(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_dc [8];
  int local_d4;
  int local_d0;
  undefined1 local_cc [184];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e07b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  local_d4 = FUN_00732ef0(&param_1);
  local_d0 = local_d4 / 2;
  while (0 < local_d0) {
    local_d0 = local_d0 + -1;
    FUN_00732eb0(local_dc,local_d0);
    uVar2 = FUN_00772230(uVar1);
    uVar2 = FUN_00417780(uVar2);
    FUN_004828f0(uVar2);
    local_8 = 0;
    uVar2 = FUN_00417780(local_cc,param_5);
    FUN_00773220(param_1,param_2,local_d0,local_d4,uVar2);
    local_8 = 0xffffffff;
    FUN_00482800();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

