
void FUN_00745fa0(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  *param_1)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  undefined1 local_44 [48];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b6d0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  cVar1 = FUN_0041f890(local_14);
  if (cVar1 == '\0') {
    pcVar2 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             operator[](param_1,0);
    if (*pcVar2 == '~') {
      uVar3 = basic_string<>(&DAT_0089ace0);
      local_8 = 0;
      FUN_00426a20(local_44,uVar3,param_1);
      local_8 = CONCAT31(local_8._1_3_,2);
      ~basic_string<>();
      cVar1 = FUN_007458a0(param_1);
      if (cVar1 != '\0') {
        FUN_007476a0();
      }
      local_8 = 0xffffffff;
      ~basic_string<>();
    }
    else {
      cVar1 = FUN_007458a0(param_1);
      if (cVar1 != '\0') {
        FUN_007476a0();
      }
    }
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

