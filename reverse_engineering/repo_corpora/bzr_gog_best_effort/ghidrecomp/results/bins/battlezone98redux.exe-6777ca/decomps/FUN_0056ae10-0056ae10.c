
undefined4 FUN_0056ae10(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  char *local_10;
  char *local_c;
  
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &DAT_009c8e28,"");
  FUN_005d48d0();
  cVar1 = operator!=<>(&DAT_009c8e28,&DAT_008a1ad8);
  if (cVar1 == '\0') {
    uVar2 = 0;
  }
  else {
    local_10 = (char *)FUN_0041f870();
    local_c = param_1;
    do {
      cVar1 = *local_10;
      *local_c = cVar1;
      local_10 = local_10 + 1;
      local_c = local_c + 1;
    } while (cVar1 != '\0');
    uVar2 = 1;
  }
  return uVar2;
}

