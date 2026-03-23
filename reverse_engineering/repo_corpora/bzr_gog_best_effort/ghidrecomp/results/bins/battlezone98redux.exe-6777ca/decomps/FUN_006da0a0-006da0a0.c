
_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_> * __thiscall
FUN_006da0a0(_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>
             *param_1,undefined4 param_2,undefined4 param_3)

{
  allocator<char> *paVar1;
  undefined1 *puVar2;
  undefined1 local_7;
  allocator<char> local_6;
  undefined1 local_5;
  
  paVar1 = (allocator<char> *)std::allocator<char>::allocator<char>(&local_6);
  std::_String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>::
  _String_alloc<0,struct_std::_String_base_types<char,class_std::allocator<char>_>_>(param_1,paVar1)
  ;
  FID_conflict__Tidy(0,0);
  puVar2 = (undefined1 *)_Iter_cat<>(&local_7,&param_2);
  local_5 = *puVar2;
  FUN_006e8710(param_2,param_3,local_5);
  return param_1;
}

