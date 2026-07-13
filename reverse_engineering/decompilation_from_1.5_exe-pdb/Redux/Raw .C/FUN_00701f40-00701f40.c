
void __fastcall FUN_00701f40(undefined4 param_1)

{
  char cVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  undefined4 uVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00856860;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  cVar1 = FUN_006ab7d0(local_14,param_1);
  if (cVar1 == '\0') {
    FUN_0070f160(6);
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  else {
    basic_string<>();
    local_8._0_1_ = 1;
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              (local_2c,1,-1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::append
              (local_2c,1,'\0');
    pbVar2 = local_2c;
    FUN_00421ec0(pbVar2);
    FUN_00705200(pbVar2);
    uVar3 = 1;
    FUN_00421ec0(1);
    FUN_00705160(uVar3);
    FUN_006ab750();
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    local_8 = 0xffffffff;
    FUN_006ca8c0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

