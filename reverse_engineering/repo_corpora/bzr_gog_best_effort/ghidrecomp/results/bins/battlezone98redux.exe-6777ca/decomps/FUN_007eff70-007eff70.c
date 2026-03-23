
void FUN_007eff70(allocator<char> *param_1,undefined4 param_2)

{
  char cVar1;
  undefined1 *puVar2;
  undefined1 local_10 [4];
  _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> local_c [7];
  undefined1 local_5;
  
  FUN_0072f050(local_10,param_2);
  FUN_0072f030(local_c,param_2);
  while( true ) {
    cVar1 = FID_conflict_operator__(local_10);
    if (cVar1 == '\0') break;
    puVar2 = (undefined1 *)get();
    local_5 = FUN_007f0bc0(*puVar2);
    puVar2 = &local_5;
    std::allocator<char>::allocator<char>(param_1);
    FUN_007f0750(puVar2);
    FUN_007efea0();
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++(local_c);
  }
  FUN_007eba50(param_1);
  return;
}

