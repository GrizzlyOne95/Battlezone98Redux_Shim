
undefined4 FUN_0071b880(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  uint uVar2;
  char *pcVar3;
  undefined1 local_14 [4];
  undefined4 local_10;
  uint local_c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_8;
  
  puVar1 = (undefined4 *)FID_conflict_begin(local_14);
  local_10 = *puVar1;
  local_c = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Pdif
                      (param_2,local_10);
  uVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::_Pdif
                    (param_3,param_2);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
            (local_8,local_c,uVar2);
  pcVar3 = std::_String_val<struct_std::_Simple_types<char>_>::_Myptr
                     ((_String_val<struct_std::_Simple_types<char>_> *)local_8);
  _String_iterator<>(pcVar3 + local_c,local_8);
  return param_1;
}

