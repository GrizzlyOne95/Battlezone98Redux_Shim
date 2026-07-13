
basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> * __thiscall
FUN_00766560(undefined4 param_1,
            basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined1 *puVar6;
  uint uVar7;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0085d208;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar7 = 0;
  local_8 = 0;
  local_14 = 0;
  do {
    if (4 < local_14) {
      basic_string<>(&DAT_008a1ad8);
      local_8 = 0xffffffff;
      ~basic_string<>(uVar2,param_1,uVar7 | 1);
      ExceptionList = local_10;
      return param_2;
    }
    for (local_18 = 0; uVar3 = FUN_00766f80(), local_18 < uVar3; local_18 = local_18 + 1) {
      puVar6 = &stack0x00000008;
      uVar4 = FUN_00766fa0(local_18);
      cVar1 = FUN_00427310(uVar4,puVar6);
      if (cVar1 != '\0') {
        iVar5 = FUN_00766fa0(local_18);
        std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
        basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                  (param_2,(basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                            *)(iVar5 + 0x48));
        local_8 = 0xffffffff;
        ~basic_string<>(uVar2,param_1,uVar7 | 1);
        ExceptionList = local_10;
        return param_2;
      }
    }
    local_14 = local_14 + 1;
  } while( true );
}

