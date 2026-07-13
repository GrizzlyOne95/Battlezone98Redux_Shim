
int * __thiscall FUN_006db9f0(int *param_1,undefined4 *param_2,facet *param_3)

{
  _Locimp *p_Var1;
  uint uVar2;
  
  p_Var1 = std::locale::_Locimp::_New_Locimp((_Locimp *)*param_2);
  *param_1 = (int)p_Var1;
  if (param_3 != (facet *)0x0) {
    uVar2 = std::locale::id::operator_unsigned_int((id *)&DAT_02cc3798);
    std::locale::_Locimp::_Addfac((_Locimp *)*param_1,param_3,uVar2);
    uVar2 = std::locale::facet::_Getcat((facet **)0x0,(locale *)0x0);
    if (uVar2 != 0xffffffff) {
      *(undefined4 *)(*param_1 + 0x10) = 0;
      std::_Yarn<char>::operator=((_Yarn<char> *)(*param_1 + 0x18),"*");
    }
  }
  return param_1;
}

