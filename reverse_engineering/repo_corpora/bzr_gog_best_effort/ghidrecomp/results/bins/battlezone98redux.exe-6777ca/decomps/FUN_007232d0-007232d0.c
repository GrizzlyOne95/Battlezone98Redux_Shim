
undefined4 *
FUN_007232d0(undefined4 *param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2,
            undefined4 param_3,undefined4 param_4,undefined4 param_5,undefined4 param_6)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  char *pcVar4;
  undefined4 local_8;
  
  FUN_007286d0(&local_8,param_2,param_4,param_5);
  cVar1 = FUN_0041f890();
  if (cVar1 == '\0') {
    while( true ) {
      cVar1 = FID_conflict_operator__(&param_6);
      if (cVar1 == '\0') break;
      uVar2 = FUN_00421ec0();
      FUN_00726500(uVar2);
      pcVar3 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               front(param_2);
      pcVar4 = (char *)FUN_00421ec0();
      *pcVar4 = *pcVar3;
      FUN_00726470();
      FUN_004f5330();
    }
    *param_1 = local_8;
  }
  else {
    cVar1 = FID_conflict_operator__(&param_5);
    if (cVar1 == '\0') {
      FUN_006da1d0(param_1,param_5,param_6,local_8);
    }
    else {
      *param_1 = param_6;
    }
  }
  return param_1;
}

