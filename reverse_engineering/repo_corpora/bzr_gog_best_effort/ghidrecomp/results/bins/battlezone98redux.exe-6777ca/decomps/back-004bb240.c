
/* Library Function - Single Match
    public: wchar_t & __thiscall std::basic_string<wchar_t,struct std::char_traits<wchar_t>,class
   std::allocator<wchar_t> >::back(void)
   
   Libraries: Visual Studio 2017 Debug, Visual Studio 2017 Release */

wchar_t * __thiscall
std::basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::back
          (basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
           *this)

{
  uint uVar1;
  undefined1 local_40 [12];
  undefined1 local_34 [12];
  wchar_t *local_28;
  undefined4 local_24;
  undefined4 local_20;
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *local_1c;
  _String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *local_18;
  basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_> *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849af0;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = this;
  local_1c = (_String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_> *)
             FUN_004bb570(local_40);
  local_8 = 0;
  local_18 = local_1c;
  local_24 = _String_iterator<class_std::_String_val<struct_std::_Simple_types<wchar_t>_>_>::
             operator-(local_1c,(int)local_34);
  local_8._0_1_ = 1;
  local_20 = local_24;
  local_28 = (wchar_t *)FUN_004bba50(uVar1);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_004bb3b0();
  local_8 = 0xffffffff;
  FUN_004bb3b0();
  ExceptionList = local_10;
  return local_28;
}

