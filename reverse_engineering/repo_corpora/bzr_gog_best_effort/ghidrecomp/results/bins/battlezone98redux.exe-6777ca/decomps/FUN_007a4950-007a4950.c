
void FUN_007a4950(void)

{
  char cVar1;
  undefined2 uVar2;
  int iVar3;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar4;
  undefined4 uVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084e248;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar3 = FUN_007cb1a0(local_14);
  if (iVar3 != 0) {
    pbVar4 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_007cf960();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar4);
    local_8 = 0;
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      uVar5 = FUN_0041f870();
      uVar2 = FUN_0056f920(uVar5);
      FUN_006247a0(uVar2);
      FUN_007cf9f0();
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

