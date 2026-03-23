
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00416150(void)

{
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_008653ce;
  local_c = ExceptionList;
  if ((DAT_00914d1c & 1) == 0) {
    DAT_00914d1c = DAT_00914d1c | 1;
    local_4 = 0;
    _DAT_00914d18 = boost::system::_anon_56EC52FE::system_error_category::vftable;
    ExceptionList = &local_c;
    FUN_0083e979(&LAB_008681e0,DAT_008e7000 ^ (uint)&local_c);
  }
  _DAT_00914cf0 = &DAT_00914d18;
  ExceptionList = local_c;
  return;
}

