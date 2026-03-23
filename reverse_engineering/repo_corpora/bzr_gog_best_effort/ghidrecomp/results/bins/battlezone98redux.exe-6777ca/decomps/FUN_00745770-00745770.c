
void __thiscall
FUN_00745770(int param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  uint uVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_94 [8];
  undefined4 uStack_8c;
  undefined1 *puStack_88;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbStack_84;
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085b5a0;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  pbStack_84 = param_2;
  puStack_88 = local_5c;
  uStack_8c = 0x7457ad;
  FUN_0048b7d0();
  local_8 = 0;
  pbStack_84 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x7457c9;
  FUN_0081e8a0();
  pbStack_84 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x7457d0;
  FUN_0081e6c0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  pbStack_84 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x7457eb;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,param_2);
  local_8 = 1;
  if (*(char *)(param_1 + 0xc0) == '\x01') {
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
              (abStack_94,local_2c);
    FUN_0073bdb0(local_44);
    pbStack_84 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
                 0x745836;
    FUN_0045e0f0();
    ~basic_string<>();
  }
  pbStack_84 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               0x74584d;
  FUN_00747e10();
  uVar1 = FUN_004170c0();
  if (1000 < uVar1) {
    FUN_00747f30();
  }
  FUN_007476a0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

