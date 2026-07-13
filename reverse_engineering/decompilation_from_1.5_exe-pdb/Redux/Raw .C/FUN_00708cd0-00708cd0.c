
void FUN_00708cd0(undefined4 param_1,undefined4 param_2,int *param_3)

{
  int iVar1;
  
  iVar1 = std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
          operator-((_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
                    &param_2,(_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                              *)&param_1);
  *param_3 = iVar1 + *param_3;
  return;
}

