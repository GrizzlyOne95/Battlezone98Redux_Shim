
void __fastcall FUN_007681d0(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar1 = *(undefined4 *)(param_1 + 0x8c);
  local_14 = uVar2;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            (local_2c,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                       *)(param_1 + 0x90));
  local_8 = 0;
  switch(uVar1) {
  case 1:
    FUN_0076a430();
    break;
  case 2:
    FUN_0076a240();
    break;
  case 3:
    FUN_0076a030(uVar2);
  case 4:
    FUN_0076a030(uVar2);
  }
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

