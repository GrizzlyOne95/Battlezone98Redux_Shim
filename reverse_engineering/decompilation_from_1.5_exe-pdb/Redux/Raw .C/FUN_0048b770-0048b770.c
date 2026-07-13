
_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_> * __thiscall
FUN_0048b770(_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>
             *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  allocator<char> *paVar1;
  allocator<char> local_6;
  undefined1 local_5;
  
  paVar1 = (allocator<char> *)std::allocator<char>::allocator<char>(&local_6);
  std::_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>::
  _String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>(param_1,paVar1)
  ;
  FID_conflict__Tidy(0,0);
  local_5 = _Ptr_cat<>(&param_2);
  FUN_0048bc30(param_2,param_3,param_4,param_5,local_5);
  return param_1;
}

