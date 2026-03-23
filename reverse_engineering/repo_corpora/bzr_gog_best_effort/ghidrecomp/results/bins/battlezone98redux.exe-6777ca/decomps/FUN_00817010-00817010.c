
int FUN_00817010(char *param_1,undefined4 *param_2)

{
  char cVar1;
  undefined1 *puVar2;
  _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *p_Var3;
  undefined1 local_1c [4];
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  char *local_c;
  char local_5;
  
  cVar1 = FID_conflict_operator__(&stack0x0000000c);
  if (cVar1 == '\0') {
    local_10 = *param_2;
    local_18 = *param_2;
    local_c = param_1;
    local_14 = 0;
    while ((local_c != (char *)0x0 &&
           (cVar1 = FID_conflict_operator__(&stack0x0000000c), cVar1 != '\0'))) {
      puVar2 = (undefined1 *)get();
      local_5 = FUN_007f0bc0(*puVar2);
      if (local_5 == *local_c) {
        if (*(int *)(local_c + 4) != 0) {
          local_14 = *(int *)(local_c + 4);
          local_18 = local_10;
        }
        local_c = *(char **)(local_c + 0xc);
        FUN_007fd380(local_1c,0);
      }
      else if (local_5 < *local_c) {
        local_c = *(char **)(local_c + 8);
      }
      else {
        local_c = *(char **)(local_c + 0x10);
      }
    }
    if (local_14 != 0) {
      p_Var3 = std::
               _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
               operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                           *)&local_18);
      *param_2 = *(undefined4 *)p_Var3;
    }
  }
  else {
    local_14 = 0;
  }
  return local_14;
}

