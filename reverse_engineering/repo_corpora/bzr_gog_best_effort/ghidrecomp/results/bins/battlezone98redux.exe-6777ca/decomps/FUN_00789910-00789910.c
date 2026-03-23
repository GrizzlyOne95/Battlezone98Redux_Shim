
void FUN_00789910(void)

{
  char cVar1;
  int iVar2;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar3;
  undefined1 *puVar4;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> abStack_64 [12];
  undefined4 uStack_58;
  undefined1 *puStack_54;
  int iStack_50;
  int iStack_4c;
  uint uStack_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined1 *local_3c;
  undefined4 local_38;
  int local_34;
  int local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085e700;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  iStack_4c = 0x789949;
  local_14 = uStack_48;
  local_34 = FUN_007cb0a0();
  if (local_34 != -1) {
    iStack_4c = 0x789960;
    cVar1 = FUN_007d3360();
    if (cVar1 != '\0') {
      iStack_4c = local_34;
      iStack_50 = 0x7899b0;
      FUN_00764790();
      iStack_50 = 0x7899ba;
      FUN_00752d30();
      iStack_4c = 0x7899c4;
      iStack_4c = FUN_0041f870();
      iStack_50 = 0x7899ca;
      iVar2 = FUN_00481f10();
      if (iVar2 == 0) {
        iStack_4c = 0;
        iStack_50 = 0x789a35;
        (**(code **)(**(int **)(local_30 + 0x150) + 0x24))();
      }
      else {
        iStack_4c = local_34;
        iStack_50 = 0x7899da;
        FUN_00764790();
        iStack_50 = 0x7899e4;
        FUN_00752d30();
        iStack_4c = 0x7899ee;
        iStack_4c = FUN_0041f870();
        iStack_50 = 0x7899fd;
        FUN_007d2870();
        iStack_4c = 1;
        iStack_50 = 0x789a18;
        (**(code **)(**(int **)(local_30 + 0x150) + 0x24))();
      }
      iStack_50 = local_34;
      puStack_54 = (undefined1 *)0x789a3e;
      FUN_00764790();
      puStack_54 = (undefined1 *)0x789a48;
      pbVar3 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
               FUN_00752d30();
      local_3c = abStack_64;
      local_44 = std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
                 basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
                           (abStack_64,pbVar3);
      local_8 = 0;
      puVar4 = local_2c;
      local_38 = local_44;
      FUN_00764790(puVar4);
      local_8 = 0xffffffff;
      local_40 = FUN_0076eb90(puVar4);
      local_8 = 1;
      iStack_50 = 3;
      puStack_54 = (undefined1 *)0x789a91;
      puStack_54 = (undefined1 *)FUN_0041f870();
      uStack_58 = 0x789aab;
      (**(code **)(**(int **)(local_30 + 0x154) + 0x3c))();
      local_8 = 0xffffffff;
      uStack_58 = 0x789aba;
      ~basic_string<>();
      goto LAB_00789aba;
    }
  }
  iStack_4c = 0;
  iStack_50 = 0x789982;
  (**(code **)(**(int **)(local_30 + 0x150) + 0x24))();
  iStack_50 = 3;
  puStack_54 = &DAT_008a1ad8;
  uStack_58 = 0x7899a2;
  (**(code **)(**(int **)(local_30 + 0x154) + 0x3c))();
LAB_00789aba:
  ExceptionList = local_10;
  puStack_54 = (undefined1 *)0x789acf;
  FUN_0083e885();
  return;
}

