
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_00840370(void)

{
  uint uVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_008656be;
  local_c = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&local_c;
  if ((DAT_0091509c & 1) == 0) {
    DAT_0091509c = DAT_0091509c | 1;
    local_4 = 0;
    DAT_00915098 = 7;
    _DAT_00915094 = 0;
    DAT_00915084._0_2_ = 0;
    ExceptionList = &local_c;
    FUN_0083fdc0(&DAT_00870c40,1);
    FUN_0083e979(&LAB_008682b0,uVar1);
  }
  ExceptionList = local_c;
  return &DAT_00915084;
}

