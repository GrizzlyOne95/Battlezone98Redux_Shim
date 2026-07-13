
void __fastcall FUN_004487d0(exception *param_1)

{
  char cVar1;
  char *pcVar2;
  undefined4 uVar3;
  uint uStack_54;
  undefined1 local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846158;
  local_10 = ExceptionList;
  uStack_54 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_54;
  ExceptionList = &local_10;
  local_18 = uStack_54;
  cVar1 = FUN_0041f890();
  if (cVar1 != '\0') {
    local_8 = 0;
    pcVar2 = std::exception::what(param_1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (param_1 + 0x14),pcVar2);
    cVar1 = FUN_0041f890();
    if (cVar1 == '\0') {
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (param_1 + 0x14),": ");
    }
    uVar3 = FUN_004486a0(local_30);
    local_8._0_1_ = 1;
    FUN_00449810(uVar3);
    local_8 = (uint)local_8._1_3_ << 8;
    ~basic_string<>();
    FUN_004488ad();
    return;
  }
  local_8 = 0xffffffff;
  FUN_0041f870();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

