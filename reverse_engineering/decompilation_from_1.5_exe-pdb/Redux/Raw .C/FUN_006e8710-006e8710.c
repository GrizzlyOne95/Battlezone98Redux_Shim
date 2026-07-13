
void FUN_006e8710(undefined4 param_1,undefined4 param_2)

{
  char *pcVar1;
  uint uStack_34;
  uint local_20;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *local_1c;
  char local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008547b0;
  local_10 = ExceptionList;
  uStack_34 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_34;
  ExceptionList = &local_10;
  local_20 = 0;
  _Distance<>(param_1,param_2,&local_20);
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::reserve
            (local_1c,local_20);
  local_8 = 0;
  while( true ) {
    local_15 = FID_conflict_operator__(&param_2);
    if (local_15 == '\0') break;
    pcVar1 = (char *)FUN_00421ec0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              (local_1c,1,*pcVar1);
    FUN_004f5330();
  }
  FUN_006e87c9();
  return;
}

