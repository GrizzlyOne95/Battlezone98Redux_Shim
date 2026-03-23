
undefined4 *
FUN_007286d0(undefined4 *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  while( true ) {
    cVar1 = FUN_0041f890();
    if (cVar1 != '\0') break;
    cVar1 = FID_conflict_operator__(&stack0x00000010);
    if (cVar1 == '\0') break;
    pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             front(param_2);
    pcVar3 = (char *)FUN_00421ec0();
    *pcVar3 = *pcVar2;
    FUN_00726470();
    FUN_004f5330();
  }
  *param_1 = param_3;
  return param_1;
}

