
void FUN_006b5220(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined1 local_78 [4];
  undefined1 local_74 [4];
  undefined1 local_70 [4];
  undefined1 local_6c [4];
  undefined1 local_68 [4];
  undefined1 local_64 [4];
  undefined1 local_60 [4];
  undefined1 local_5c [4];
  undefined1 local_58 [4];
  undefined1 local_54 [4];
  undefined1 local_50 [4];
  undefined1 local_4c [4];
  undefined1 local_48 [8];
  uint local_40;
  undefined4 local_3c;
  int local_38;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_34;
  undefined4 local_30;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008509d6;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>(local_14);
  local_8 = 0;
  basic_string<>();
  local_8._0_1_ = 1;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,2);
  local_34[0x4b] = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0
  ;
  FUN_00423890();
  FUN_00423890();
  local_38 = 0;
  puVar3 = (undefined4 *)FID_conflict_begin(local_74);
  local_30 = *puVar3;
  local_40 = FUN_004170c0();
  if (local_40 < 7) {
LAB_006b5304:
    if (5 < local_40) {
      pcVar5 = "ws://";
      puVar3 = (undefined4 *)
               std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               iterator::operator+((iterator *)&local_30,(int)local_78);
      cVar1 = FUN_006d9a00(local_30,*puVar3,pcVar5);
      if (cVar1 != '\0') {
        local_34[0x4a] =
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_34,"ws");
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator
        ::operator+=((iterator *)&local_30,5);
        goto LAB_006b53f9;
      }
    }
    if (7 < local_40) {
      pcVar5 = "http://";
      puVar3 = (undefined4 *)
               std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               iterator::operator+((iterator *)&local_30,(int)local_54);
      cVar1 = FUN_006d9a00(local_30,*puVar3,pcVar5);
      if (cVar1 != '\0') {
        local_34[0x4a] =
             (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x0;
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                  (local_34,"http");
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator
        ::operator+=((iterator *)&local_30,7);
        goto LAB_006b53f9;
      }
    }
    if (local_40 < 9) goto LAB_006b567a;
    pcVar5 = "https://";
    puVar3 = (undefined4 *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             iterator::operator+((iterator *)&local_30,(int)local_4c);
    cVar1 = FUN_006d9a00(local_30,*puVar3,pcVar5);
    if (cVar1 == '\0') goto LAB_006b567a;
    local_34[0x4a] =
         (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x1;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_34,"https");
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator::
    operator+=((iterator *)&local_30,8);
  }
  else {
    pcVar5 = "wss://";
    puVar3 = (undefined4 *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             iterator::operator+((iterator *)&local_30,(int)local_70);
    cVar1 = FUN_006d9a00(local_30,*puVar3,pcVar5);
    if (cVar1 == '\0') goto LAB_006b5304;
    local_34[0x4a] =
         (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x1;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_34,(char *)&PTR_LAB_00896ca8);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::iterator::
    operator+=((iterator *)&local_30,6);
  }
LAB_006b53f9:
  pcVar5 = (char *)get();
  if (*pcVar5 == '[') {
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_30);
    local_3c = local_30;
    while( true ) {
      uVar4 = FUN_004fee40(local_5c);
      cVar1 = FID_conflict_operator__(uVar4);
      if ((cVar1 == '\0') || (pcVar5 = (char *)get(), *pcVar5 == ']')) break;
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                  *)&local_3c);
    }
    uVar4 = FUN_004fee40(local_6c);
    cVar1 = FID_conflict_operator__(uVar4);
    if (cVar1 != '\0') goto LAB_006b567a;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    assign<class_std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
              (local_34 + 0x18,local_30,local_3c);
    puVar3 = (undefined4 *)
             std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             iterator::operator+((iterator *)&local_3c,(int)local_64);
    local_30 = *puVar3;
    uVar4 = FUN_004fee40(local_50);
    cVar1 = FID_conflict_operator__(uVar4);
    if (cVar1 == '\0') {
      pcVar5 = (char *)get();
      if (*pcVar5 == '/') {
        local_38 = 2;
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_30);
      }
      else {
        pcVar5 = (char *)get();
        if (*pcVar5 != ':') goto LAB_006b567a;
        local_38 = 1;
        std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
        operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                    *)&local_30);
      }
    }
    else {
      local_38 = 2;
    }
  }
  else {
    while (local_38 == 0) {
      uVar4 = FUN_004fee40(local_58);
      cVar1 = FID_conflict_operator__(uVar4);
      if (cVar1 != '\0') {
        local_38 = 2;
        break;
      }
      pcVar5 = (char *)get();
      if (*pcVar5 == '/') {
        local_38 = 2;
      }
      else {
        pcVar5 = (char *)get();
        if (*pcVar5 == ':') {
          local_38 = 1;
        }
        else {
          pcVar5 = (char *)get();
          std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
          operator+=(local_34 + 0x18,*pcVar5);
        }
      }
      std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
      operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>
                  *)&local_30);
    }
  }
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,3);
  while (local_38 == 1) {
    uVar4 = FUN_004fee40(local_60);
    cVar1 = FID_conflict_operator__(uVar4);
    if (cVar1 != '\0') break;
    pcVar5 = (char *)get();
    if (*pcVar5 == '/') {
      local_38 = 3;
    }
    else {
      pcVar5 = (char *)get();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator+=
                (local_2c,*pcVar5);
    }
    std::_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>::
    operator++((_String_const_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_> *)
               &local_30);
  }
  FUN_006ab750();
  uVar2 = FUN_006b61b0(local_2c,local_48);
  *(undefined2 *)(local_34 + 0x48) = uVar2;
  cVar1 = FUN_006ab7d0();
  if (cVar1 == '\0') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_34 + 0x30,"/");
    puVar3 = (undefined4 *)FUN_004fee40(local_68);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    assign<class_std::_String_iterator<class_std::_String_val<struct_std::_Simple_types<char>_>_>_>
              (local_34 + 0x30,local_30,*puVar3);
    local_34[0x4b] =
         (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>)0x1;
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
  }
  else {
    local_8 = CONCAT31(local_8._1_3_,2);
    ~basic_string<>();
  }
LAB_006b567a:
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

