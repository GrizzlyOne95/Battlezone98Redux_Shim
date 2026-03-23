
void FUN_0074b7c0(undefined4 param_1,
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_84 [8];
  undefined4 uStack_7c;
  undefined1 *puStack_78;
  undefined4 uStack_74;
  undefined1 *puStack_70;
  uint uStack_6c;
  undefined4 local_68;
  undefined1 *local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085bc58;
  local_10 = ExceptionList;
  uStack_6c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puStack_70 = (undefined1 *)0x74b7f9;
  local_14 = uStack_6c;
  iVar1 = get();
  if (*(char *)(iVar1 + 0xc34) == '\0') {
    puStack_70 = (undefined1 *)0x74b812;
    get();
    puStack_70 = (undefined1 *)0x74b819;
    FUN_006c6320();
  }
  puStack_70 = local_44;
  uStack_74 = 0x74b825;
  local_60 = FUN_0073a9f0();
  local_8 = 0;
  puStack_70 = (undefined1 *)0xffffffff;
  uStack_74 = 1;
  puStack_78 = local_2c;
  uStack_7c = 0x74b849;
  local_5c = local_60;
  puStack_78 = (undefined1 *)FUN_0045e1d0();
  local_8._0_1_ = 1;
  puStack_70 = (undefined1 *)0xa;
  uStack_74 = 0;
  uStack_7c = 0x74b863;
  local_58 = puStack_78;
  local_54 = puStack_78;
  local_50 = FUN_0074b350();
  local_8 = (uint)local_8._1_3_ << 8;
  puStack_70 = (undefined1 *)0x74b875;
  ~basic_string<>();
  local_8 = 0xffffffff;
  puStack_70 = (undefined1 *)0x74b884;
  ~basic_string<>();
  local_64 = abStack_84;
  local_68 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
             basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       (abStack_84,param_2);
  local_8 = 2;
  uVar2 = local_50;
  local_4c = local_68;
  get(local_50);
  local_8 = 0xffffffff;
  FUN_006c46b0(uVar2);
  ExceptionList = local_10;
  uStack_6c = 0x74b8da;
  FUN_0083e885();
  return;
}

