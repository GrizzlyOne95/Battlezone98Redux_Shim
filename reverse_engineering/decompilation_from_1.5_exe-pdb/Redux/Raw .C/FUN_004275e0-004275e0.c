
facet * FUN_004275e0(locale *param_1)

{
  uint uVar1;
  uint uVar2;
  bad_cast local_34 [12];
  facet *local_28;
  _Lockit local_24 [4];
  uint local_20;
  facet *local_1c;
  facet *local_18;
  facet *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845539;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  std::_Lockit::_Lockit(local_24,0);
  local_8 = 0;
  local_14 = (facet *)DAT_02cc2b68;
  local_20 = std::locale::id::operator_unsigned_int((id *)id_exref);
  local_18 = (facet *)FUN_00417ba0(local_20);
  if (local_18 == (facet *)0x0) {
    if (local_14 == (facet *)0x0) {
      uVar2 = std::codecvt<char,char,int>::_Getcat(&local_14,param_1);
      if (uVar2 == 0xffffffff) {
        std::bad_cast::bad_cast(local_34,"bad cast");
                    /* WARNING: Subroutine does not return */
        _CxxThrowException(local_34,(ThrowInfo *)&DAT_008d7aac);
      }
      local_18 = local_14;
      DAT_02cc2b68 = (int *)local_14;
      local_1c = local_14;
      (**(code **)(*(int *)local_14 + 4))(uVar1);
      Facet_Register(local_1c);
    }
    else {
      local_18 = local_14;
    }
  }
  local_28 = local_18;
  local_8 = 0xffffffff;
  std::_Lockit::~_Lockit(local_24);
  ExceptionList = local_10;
  return local_28;
}

