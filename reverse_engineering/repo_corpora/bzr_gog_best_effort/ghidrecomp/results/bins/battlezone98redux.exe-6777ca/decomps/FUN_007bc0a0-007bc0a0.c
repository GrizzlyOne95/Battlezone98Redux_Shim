
void __thiscall FUN_007bc0a0(int param_1,undefined1 param_2)

{
  char cVar1;
  uint uVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  char *pcVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar2;
  if (*(int *)(param_1 + 0x150) != 0) {
    FUN_007cafa0(0xffffffff);
    FUN_007cfa70(param_2);
    (**(code **)(**(int **)(param_1 + 0x14c) + 0x24))(0,uVar2);
    pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_007cf960();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
    basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,pbVar3);
    local_8 = 0;
    cVar1 = operator!=<>(local_2c,&DAT_008a1ad8);
    if (cVar1 != '\0') {
      (**(code **)(**(int **)(param_1 + 0x14c) + 0x24))(1);
    }
    cVar1 = FUN_0041f890();
    if ((cVar1 == '\0') &&
       (pcVar4 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 operator[](local_2c,0), *pcVar4 == '.')) {
      (**(code **)(**(int **)(param_1 + 0x14c) + 0x24))(0);
    }
    local_8 = 0xffffffff;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

