
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_008402e0(void)

{
  uint uVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0086568e;
  local_c = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&local_c;
  if ((DAT_009150b8 & 1) == 0) {
    DAT_009150b8 = DAT_009150b8 | 1;
    local_4 = 0;
    DAT_009150b4 = 7;
    _DAT_009150b0 = 0;
    DAT_009150a0._0_2_ = 0;
    ExceptionList = &local_c;
    FUN_0083fdc0(&DAT_00870c44,2);
    FUN_0083e979(&LAB_00868250,uVar1);
  }
  ExceptionList = local_c;
  return &DAT_009150a0;
}

