
void FUN_007bb210(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  uint uStack_a8;
  undefined1 local_48 [24];
  undefined1 local_30 [24];
  uint local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00861760;
  local_10 = ExceptionList;
  uStack_a8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_a8;
  ExceptionList = &local_10;
  local_18 = uStack_a8;
  iVar2 = get();
  if (iVar2 == 0) {
    FUN_004487d0();
    FUN_007bb479();
    return;
  }
  local_8 = 0;
  get();
  cVar1 = FUN_0041f890();
  if (cVar1 != '\0') {
    iVar2 = get();
    pcVar3 = (char *)FUN_004487d0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               (iVar2 + 0x30),pcVar3);
    get();
    cVar1 = FUN_006e1c30();
    if (cVar1 == '\0') {
      iVar2 = get();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar2 + 0x30),": \"");
      get();
      uVar4 = FUN_00417fd0(local_30);
      local_8._0_1_ = 1;
      get();
      FUN_00449810(uVar4);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      iVar2 = get();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar2 + 0x30),"\"");
    }
    get();
    cVar1 = FUN_006e1c30();
    if (cVar1 == '\0') {
      iVar2 = get();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar2 + 0x30),", \"");
      get();
      uVar4 = FUN_00417fd0(local_48);
      local_8._0_1_ = 2;
      get();
      FUN_00449810(uVar4);
      local_8 = (uint)local_8._1_3_ << 8;
      ~basic_string<>();
      iVar2 = get();
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 (iVar2 + 0x30),"\"");
    }
  }
  get();
  FUN_0041f870();
  FUN_007bb479();
  return;
}

