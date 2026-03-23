
facet * FUN_0083f7e0(locale *param_1)

{
  int iVar1;
  uint uVar2;
  _Locimp *p_Var3;
  facet *pfVar4;
  facet *local_20;
  _Lockit local_1c [4];
  bad_cast local_18 [12];
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865539;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  std::_Lockit::_Lockit(local_1c,0);
  local_4 = 0;
  local_20 = (facet *)DAT_009150c4;
  uVar2 = std::locale::id::operator_unsigned_int((id *)id_exref);
  iVar1 = *(int *)param_1;
  if (uVar2 < *(uint *)(iVar1 + 0xc)) {
    pfVar4 = *(facet **)(*(int *)(iVar1 + 8) + uVar2 * 4);
    if (pfVar4 != (facet *)0x0) goto LAB_0083f8b9;
  }
  else {
    pfVar4 = (facet *)0x0;
  }
  if (*(char *)(iVar1 + 0x14) == '\0') {
LAB_0083f861:
    if (pfVar4 != (facet *)0x0) goto LAB_0083f8b9;
  }
  else {
    p_Var3 = std::locale::_Getgloballocale();
    if (uVar2 < *(uint *)(p_Var3 + 0xc)) {
      pfVar4 = *(facet **)(*(int *)(p_Var3 + 8) + uVar2 * 4);
      goto LAB_0083f861;
    }
  }
  pfVar4 = local_20;
  if (local_20 == (facet *)0x0) {
    uVar2 = std::codecvt<wchar_t,char,int>::_Getcat(&local_20,param_1);
    pfVar4 = local_20;
    if (uVar2 == 0xffffffff) {
      std::bad_cast::bad_cast(local_18,"bad cast");
                    /* WARNING: Subroutine does not return */
      _CxxThrowException(local_18,(ThrowInfo *)&DAT_008d7aac);
    }
    DAT_009150c4 = (int)local_20;
    (**(code **)(*(int *)local_20 + 4))();
    Facet_Register(pfVar4);
  }
LAB_0083f8b9:
  std::_Lockit::~_Lockit(local_1c);
  ExceptionList = local_c;
  return pfVar4;
}

