
void __fastcall FUN_007a3f80(int param_1)

{
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar1;
  undefined1 *puVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_5c [12];
  undefined4 uStack_50;
  undefined1 *puStack_4c;
  undefined4 uStack_48;
  uint uStack_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined1 *local_38;
  undefined4 local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860340;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30 = param_1;
  local_14 = uStack_44;
  if (*(int *)(param_1 + 0x38) == -1) {
    uStack_48 = 3;
    puStack_4c = &DAT_008a1ad8;
    uStack_50 = 0x7a3fce;
    (**(code **)(**(int **)(param_1 + 0x44) + 0x3c))();
  }
  else {
    uStack_48 = *(undefined4 *)(param_1 + 0x38);
    puStack_4c = (undefined1 *)0x7a3fe2;
    pbVar1 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             FUN_00752d30();
    local_38 = abStack_5c;
    local_40 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
               basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                         (abStack_5c,pbVar1);
    local_8 = 0;
    puVar2 = local_2c;
    local_34 = local_40;
    FUN_00764790(puVar2);
    local_8 = 0xffffffff;
    local_3c = FUN_0076eb90(puVar2);
    local_8 = 1;
    uStack_48 = 3;
    puStack_4c = (undefined1 *)0x7a402b;
    puStack_4c = (undefined1 *)FUN_0041f870();
    uStack_50 = 0x7a403f;
    (**(code **)(**(int **)(local_30 + 0x44) + 0x3c))();
    local_8 = 0xffffffff;
    uStack_50 = 0x7a404e;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  puStack_4c = (undefined1 *)0x7a4063;
  FUN_0083e885();
  return;
}

