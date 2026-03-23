
void __thiscall
FUN_007a3e60(int param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  uint local_34;
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
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>(local_2c,param_2);
  local_8 = 0;
  iVar3 = FUN_004170c0(uVar2);
  if (iVar3 != 0) {
    uVar4 = FUN_004170c0(uVar2);
    iVar3 = FUN_004170c0();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::erase
              (local_2c,iVar3 - 4,uVar4);
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_2c,".vxt");
    pbVar6 = local_2c;
    FUN_00764780(pbVar6);
    FUN_00766900(pbVar6);
  }
  *(undefined4 *)(param_1 + 0x38) = 0xffffffff;
  local_34 = 0;
  do {
    uVar4 = FUN_004170c0(uVar2);
    if (uVar4 <= local_34) {
LAB_007a3f40:
      FUN_007a3f80();
      FUN_007a4070();
      local_8 = 0xffffffff;
      ~basic_string<>();
      ExceptionList = local_10;
      FUN_0083e885();
      return;
    }
    pbVar6 = param_2;
    uVar5 = FUN_00752d30(local_34);
    cVar1 = FUN_00427310(uVar5,pbVar6);
    if (cVar1 != '\0') {
      *(uint *)(param_1 + 0x38) = local_34;
      goto LAB_007a3f40;
    }
    local_34 = local_34 + 1;
  } while( true );
}

