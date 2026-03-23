
undefined4 * __thiscall
FUN_007fd380(_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
             *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)param_1;
  std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::operator++
            (param_1);
  *param_2 = uVar1;
  return param_2;
}

