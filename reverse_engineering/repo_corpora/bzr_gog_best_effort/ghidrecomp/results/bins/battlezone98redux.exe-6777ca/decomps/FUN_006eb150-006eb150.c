
undefined1 FUN_006eb150(void)

{
  int iVar1;
  uint uVar2;
  _Lockit local_14 [4];
  uint local_10;
  undefined4 local_c;
  undefined1 local_5;
  
  std::_Lockit::_Lockit(local_14,0);
  local_10 = std::locale::id::operator_unsigned_int((id *)&DAT_02cc3798);
  iVar1 = FUN_00417ba0(local_10);
  if (iVar1 == 0) {
    uVar2 = std::locale::facet::_Getcat((facet **)0x0,(locale *)0x0);
    if (uVar2 == 0xffffffff) {
      local_c = 0;
      goto LAB_006eb1a1;
    }
  }
  local_c = 1;
LAB_006eb1a1:
  local_5 = (undefined1)local_c;
  std::_Lockit::~_Lockit(local_14);
  return local_5;
}

