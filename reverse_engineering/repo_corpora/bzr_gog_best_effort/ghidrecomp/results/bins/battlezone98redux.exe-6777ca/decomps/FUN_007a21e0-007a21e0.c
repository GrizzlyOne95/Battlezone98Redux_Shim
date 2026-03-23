
void __fastcall FUN_007a21e0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  undefined1 local_a4 [24];
  undefined1 local_8c [24];
  undefined1 local_74 [24];
  undefined1 local_5c [24];
  undefined1 local_44 [24];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00860126;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iVar1 = FUN_006cc050(local_14);
  if (iVar1 == 0) {
    FUN_0079e920(1);
    FUN_007c3040(0);
    FUN_007c3040(0);
    FUN_007c3040(0);
    FUN_007c3040(0);
    FUN_007a10c0();
  }
  else if (iVar1 == 1) {
    FUN_0079e920(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(0);
    FUN_007c3040(0);
    FUN_007c3040(0);
    FUN_007a10c0();
  }
  else if (iVar1 == 2) {
    FUN_0079e920(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007a11e0();
  }
  else if (iVar1 == 3) {
    FUN_0079e920(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(0);
    FUN_007c3040(0);
    FUN_007c3040(0);
    FUN_007a11e0();
  }
  else if (iVar1 == 4) {
    if (*(char *)(param_1 + 0x1ff) == '\0') {
      FUN_0079e920(0);
    }
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007c3040(1);
    FUN_007a11e0();
    FUN_0079e730();
    iVar1 = FUN_00765c80();
    if (iVar1 != 0) {
      uVar2 = FUN_00765c80();
      FUN_00765c90(0);
      switch(uVar2) {
      case 1:
        uVar2 = FUN_0081cb40("multi_popup","lobbyfull");
        basic_string<>(uVar2);
        local_8 = 0;
        FUN_00745770(local_44);
        local_8 = 0xffffffff;
        ~basic_string<>();
        break;
      case 2:
        uVar2 = FUN_0081cb40("multi_popup","wrongpassword");
        basic_string<>(uVar2);
        local_8 = 1;
        FUN_00745770(local_5c);
        local_8 = 0xffffffff;
        ~basic_string<>();
        break;
      case 3:
        uVar2 = FUN_0081cb40("multi_popup","lobbylocked");
        basic_string<>(uVar2);
        local_8 = 2;
        FUN_00745770(local_a4);
        local_8 = 0xffffffff;
        ~basic_string<>();
        break;
      case 4:
        uVar2 = FUN_0081cb40("multi_popup","doesnotexist");
        basic_string<>(uVar2);
        local_8 = 3;
        FUN_00745770(local_8c);
        local_8 = 0xffffffff;
        ~basic_string<>();
        break;
      case 5:
        uVar2 = FUN_0081cb40("multi_popup","alreadyamember");
        basic_string<>(uVar2);
        local_8 = 4;
        FUN_00745770(local_74);
        local_8 = 0xffffffff;
        ~basic_string<>();
      }
    }
  }
  FUN_00764760();
  uVar2 = FUN_00740e30();
  FUN_00482630(local_2c,uVar2);
  local_8 = 5;
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c," ");
  pcVar3 = (char *)FUN_0081cb40("multi_message","players");
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
            (local_2c,pcVar3);
  uVar2 = FUN_0041f870();
  (**(code **)(**(int **)(param_1 + 900) + 0x3c))(uVar2);
  FUN_00764760();
  iVar1 = FUN_00740e30();
  FUN_007cc5c0(1 < iVar1);
  FUN_007ce580();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

