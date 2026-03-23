
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00843bf0(void)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_00865dde;
  local_c = ExceptionList;
  if ((DAT_009150fc & 1) == 0) {
    DAT_009150fc = DAT_009150fc | 1;
    local_4 = 0;
    _DAT_009150f8 = _anon_B58A0D6A::codecvt_error_cat::vftable;
    ExceptionList = &local_c;
    FUN_0083e979(&LAB_00868370,DAT_008e7000 ^ (uint)&local_c);
  }
  ExceptionList = local_c;
  return &DAT_009150f8;
}

