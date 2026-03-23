
undefined4 FUN_0080e370(undefined4 *param_1,undefined4 param_2,double *param_3)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *p_Var4;
  float10 extraout_ST0;
  undefined4 local_8;
  
  cVar1 = FID_conflict_operator__(param_2);
  if (cVar1 == '\0') {
    pcVar3 = (char *)get();
    if ((*pcVar3 != 'n') && (pcVar3 = (char *)get(), *pcVar3 != 'N')) {
      return 0;
    }
    cVar1 = FUN_0080faa0(&DAT_008a1b30,&DAT_008a1cc8,param_1,param_2,&DAT_0260c0e5);
    if (cVar1 == '\0') {
      uVar2 = 0;
    }
    else {
      cVar1 = FID_conflict_operator__(param_2);
      if ((cVar1 != '\0') && (pcVar3 = (char *)get(), *pcVar3 == '(')) {
        local_8 = *param_1;
        do {
          uVar2 = param_2;
          std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
          operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                      *)&local_8);
          cVar1 = FID_conflict_operator__(uVar2);
          if (cVar1 == '\0') break;
          pcVar3 = (char *)get();
        } while (*pcVar3 != ')');
        cVar1 = FID_conflict_operator__(param_2);
        if (cVar1 != '\0') {
          return 0;
        }
        p_Var4 = std::
                 _String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
                 operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                             *)&local_8);
        *param_1 = *(undefined4 *)p_Var4;
      }
      FUN_007fad00();
      *param_3 = (double)extraout_ST0;
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

