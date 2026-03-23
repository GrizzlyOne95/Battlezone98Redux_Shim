
void __fastcall FUN_007a9ea0(int param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  basic_string<>(local_14);
  local_8 = 0;
  FUN_00764780();
  uVar1 = FUN_00766680();
  switch(uVar1) {
  case 0:
    uVar1 = FUN_0041f870();
    pcVar2 = (char *)FUN_0081cb40("faction",uVar1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,pcVar2);
    break;
  case 1:
    uVar1 = FUN_0041f870();
    pcVar2 = (char *)FUN_0081cb40("faction",uVar1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,pcVar2);
    break;
  case 2:
    uVar1 = FUN_0041f870();
    pcVar2 = (char *)FUN_0081cb40("faction",uVar1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,pcVar2);
    break;
  case 3:
    uVar1 = FUN_0041f870();
    pcVar2 = (char *)FUN_0081cb40("faction",uVar1);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,pcVar2);
    break;
  default:
    pcVar2 = (char *)FUN_0081cb40("faction","other");
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,pcVar2);
  }
  uVar1 = FUN_0041f870();
  (**(code **)(**(int **)(param_1 + 0x24) + 0x3c))(uVar1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

