
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004160e0(void)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0086539e;
  local_c = ExceptionList;
  if ((DAT_00914d24 & 1) == 0) {
    DAT_00914d24 = DAT_00914d24 | 1;
    local_4 = 0;
    _DAT_00914d20 = boost::system::_anon_56EC52FE::generic_error_category::vftable;
    ExceptionList = &local_c;
    FUN_0083e979(&LAB_008681d0,DAT_008e7000 ^ (uint)&local_c);
  }
  _DAT_00914cf8 = &DAT_00914d20;
  ExceptionList = local_c;
  return;
}

