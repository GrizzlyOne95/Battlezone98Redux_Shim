
void FUN_006f7c40(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined1 local_54 [8];
  undefined1 local_4c [4];
  undefined1 local_48 [4];
  undefined1 local_44 [4];
  undefined1 local_40 [4];
  undefined4 local_3c;
  undefined1 local_36;
  undefined1 local_35;
  uint local_34;
  undefined4 local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855768;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_34 = 0;
  basic_string<>(local_14);
  local_8 = 0;
  cVar1 = FID_conflict_operator__(&param_2);
  if (cVar1 == '\0') {
    pcVar2 = (char *)get();
    if (*pcVar2 == '\"') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator::
      operator+((iterator *)&param_2,(int)&local_30);
      local_3c = local_30;
      local_35 = 0x22;
      puVar3 = (undefined4 *)FUN_00708ba0(local_40,local_30,param_3,&local_35);
      local_30 = *puVar3;
      while( true ) {
        cVar1 = FID_conflict_operator__(&param_3);
        if (cVar1 == '\0') break;
        FID_conflict_operator_(local_48,1);
        pcVar2 = (char *)get();
        if (*pcVar2 != '\\') {
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          assign<class_std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
                    (local_2c,local_3c,local_30);
          std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
          operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                      *)&local_30);
          FUN_00708b60(param_1,local_2c,&local_30);
          local_34 = local_34 | 1;
          local_8 = 0xffffffff;
          ~basic_string<>();
          goto LAB_006f7e53;
        }
        puVar3 = (undefined4 *)FID_conflict_operator_(local_4c,1);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        assign<class_std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
                  (local_2c,local_3c,*puVar3);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
                  (local_2c,1,'\"');
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_30);
        local_3c = local_30;
        local_36 = 0x22;
        puVar3 = (undefined4 *)FUN_00708ba0(local_44,local_30,param_3,&local_36);
        local_30 = *puVar3;
      }
      uVar4 = make_pair<>(local_54,&DAT_008a1ad8,&param_2);
      FUN_00708c10(uVar4);
      local_34 = local_34 | 1;
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else {
      FUN_00708b60(param_1,local_2c,&param_2);
      local_34 = local_34 | 1;
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
  }
  else {
    FUN_00708b60(param_1,local_2c,&param_2);
    local_34 = local_34 | 1;
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
LAB_006f7e53:
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

