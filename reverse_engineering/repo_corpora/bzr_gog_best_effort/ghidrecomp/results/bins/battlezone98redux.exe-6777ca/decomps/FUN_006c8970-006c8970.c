
void __thiscall
FUN_006c8970(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_1,
            undefined1 param_2)

{
  undefined4 *puVar1;
  undefined1 local_14 [8];
  undefined4 local_c;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_8;
  
  local_8 = param_1;
  puVar1 = (undefined4 *)
           std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::end
                     (param_1);
  local_c = *puVar1;
  FUN_006cd5b0(local_14,local_c,param_2);
  return;
}

