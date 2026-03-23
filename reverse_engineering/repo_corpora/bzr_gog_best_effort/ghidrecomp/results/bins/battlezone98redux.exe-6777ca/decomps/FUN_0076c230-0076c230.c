
undefined4 FUN_0076c230(undefined4 param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  wchar_t *pwVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085d958;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar7 = 0;
  local_8 = 0;
  cVar1 = FUN_0041f890(uVar2,0);
  if (cVar1 != '\0') goto LAB_0076c2d2;
  pcVar3 = (char *)FUN_0076eef0();
  if (*pcVar3 == '\"') {
LAB_0076c290:
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               &stack0x00000008,0,1);
  }
  else {
    pcVar3 = (char *)FUN_0076eef0();
    if (*pcVar3 == -0x6d) goto LAB_0076c290;
  }
  pwVar4 = std::
           basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
           back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                 *)&stack0x00000008);
  if ((char)*pwVar4 != '\"') {
    pwVar4 = std::
             basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>::
             back((basic_string<wchar_t,struct_std::char_traits<wchar_t>,class_std::allocator<wchar_t>_>
                   *)&stack0x00000008);
    if ((char)*pwVar4 != -0x6c) goto LAB_0076c2d2;
  }
  uVar6 = 1;
  iVar5 = FUN_004170c0();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &stack0x00000008,iVar5 - 1,uVar6);
LAB_0076c2d2:
  basic_string<>(&stack0x00000008);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar2,uVar7 | 1);
  ExceptionList = local_10;
  return param_1;
}

