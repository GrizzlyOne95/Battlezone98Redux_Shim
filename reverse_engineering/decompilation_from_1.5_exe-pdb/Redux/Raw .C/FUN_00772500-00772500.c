
void FUN_00772500(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined1 param_5)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 local_d8 [8];
  int local_d0;
  int local_cc;
  undefined1 local_c8 [180];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085dffb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  local_d0 = FUN_00732ef0(&param_1);
  local_cc = local_d0 / 2;
  while (0 < local_cc) {
    local_cc = local_cc + -1;
    FUN_00732eb0(local_d8,local_cc);
    uVar2 = FUN_00772160(uVar1);
    uVar2 = FUN_00417780(uVar2);
    FUN_00753550(uVar2);
    local_8 = 0;
    uVar2 = FUN_00417780(local_c8,param_5);
    FUN_00772ec0(param_1,param_2,local_cc,local_d0,uVar2);
    local_8 = 0xffffffff;
    FUN_00753670();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

