
/* Library Function - Single Match
    public: class std::_String_iterator<class std::_String_val<struct std::_Simple_types<wchar_t> >
   > __thiscall std::_String_iterator<class std::_String_val<struct std::_Simple_types<wchar_t> >
   >::operator-(int)const 
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release */

int __thiscall
std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_>::operator-
          (_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *this,
          int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000008;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849b48;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004bbb20(this);
  local_8 = 0;
  uVar2 = FID_conflict_operator__(in_stack_00000008);
  FUN_004bbb20(uVar2);
  local_8 = 0xffffffff;
  FUN_004bb3b0(uVar1);
  ExceptionList = local_10;
  return param_1;
}

