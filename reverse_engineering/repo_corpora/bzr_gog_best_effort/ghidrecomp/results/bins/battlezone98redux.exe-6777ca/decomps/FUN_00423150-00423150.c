
basic_streambuf<char,struct_std::char_traits<char>_> * __thiscall
FUN_00423150(basic_streambuf<char,struct_std::char_traits<char>_> *param_1,char *param_2,int param_3
            ,int param_4)

{
  uint uVar1;
  _iobuf *p_Var2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845318;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if ((*(int *)(param_1 + 0x50) == 0) &&
     (p_Var2 = std::_Fiopen(param_2,param_3,param_4), p_Var2 != (_iobuf *)0x0)) {
    FUN_00423280(p_Var2,1);
    uVar3 = std::basic_streambuf<char,struct_std::char_traits<char>_>::getloc(param_1);
    local_8 = 0;
    uVar3 = FUN_004275e0(uVar3,uVar1);
    FUN_00423540(uVar3);
    local_8 = 0xffffffff;
    FUN_00417b50();
    ExceptionList = local_10;
    return param_1;
  }
  ExceptionList = local_10;
  return (basic_streambuf<char,struct_std::char_traits<char>_> *)0x0;
}

