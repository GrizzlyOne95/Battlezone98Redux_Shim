
int * FUN_008401c0(int *param_1)

{
  int iVar1;
  _Locimp *p_Var2;
  codecvt<wchar_t,char,int> *this;
  _Locimp *p_Var3;
  uint uVar4;
  undefined4 *puVar5;
  void *local_c;
  undefined1 *puStack_8;
  int local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865663;
  local_c = ExceptionList;
  ExceptionList = &local_c;
  p_Var2 = std::locale::_Init(true);
  local_4 = 0;
  this = operator_new(0x34);
  local_4._0_1_ = 1;
  if (this == (codecvt<wchar_t,char,int> *)0x0) {
    this = (codecvt<wchar_t,char,int> *)0x0;
  }
  else {
    std::codecvt<wchar_t,char,int>::codecvt<wchar_t,char,int>(this,0);
    *(undefined ***)this = windows_file_codecvt::vftable;
  }
  local_4 = (uint)local_4._1_3_ << 8;
  p_Var3 = std::locale::_Locimp::_New_Locimp(p_Var2);
  *param_1 = (int)p_Var3;
  if (this != (codecvt<wchar_t,char,int> *)0x0) {
    uVar4 = std::locale::id::operator_unsigned_int((id *)id_exref);
    std::locale::_Locimp::_Locimp_Addfac((_Locimp *)*param_1,(facet *)this,uVar4);
    uVar4 = std::codecvt<wchar_t,char,int>::_Getcat((facet **)0x0,(locale *)0x0);
    if (uVar4 != 0xffffffff) {
      iVar1 = *param_1;
      *(undefined4 *)(iVar1 + 0x10) = 0;
      std::_Yarn<char>::operator=((_Yarn<char> *)(iVar1 + 0x18),"*");
    }
  }
  local_4 = 0xffffffff;
  if (p_Var2 != (_Locimp *)0x0) {
    puVar5 = (undefined4 *)(**(code **)(*(int *)p_Var2 + 8))();
    if (puVar5 != (undefined4 *)0x0) {
      (**(code **)*puVar5)(1);
    }
  }
  ExceptionList = local_c;
  return param_1;
}

