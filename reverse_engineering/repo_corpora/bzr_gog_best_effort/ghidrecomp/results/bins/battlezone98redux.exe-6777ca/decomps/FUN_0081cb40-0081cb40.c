
void FUN_0081cb40(char *param_1,char *param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  basic_ostream<char,struct_std::char_traits<char>_> *this;
  code *pcVar5;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar6;
  undefined1 local_3c [4];
  undefined1 local_38 [4];
  undefined4 local_34;
  undefined1 local_30 [4];
  undefined4 local_2c;
  undefined4 local_28;
  uint local_24;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = FUN_0081c600(param_1,param_2);
  puVar2 = (undefined4 *)FUN_0044eb20(local_38,&local_2c);
  local_28 = *puVar2;
  uVar3 = FUN_0044eaa0(local_3c);
  cVar1 = FUN_00420f10(uVar3);
  if (cVar1 == '\0') {
    if (DAT_00946724 != 0) {
      basic_string<>(&DAT_008a1e54);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_20,param_1);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_20," | ");
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_20,param_2);
      std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
                (local_20," }");
      pcVar5 = FUN_004bc8c0;
      FUN_0081e820("Localization system missing string: ",local_20);
      uVar3 = FUN_0081e660();
      uVar3 = FUN_004bc590(uVar3);
      this = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_00574730(uVar3);
      std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(this,pcVar5);
      uVar3 = vector<>();
      FUN_0081d370(local_30,local_28,&local_2c,uVar3);
      FUN_0048a040();
      for (local_24 = 0; local_24 < 7; local_24 = local_24 + 1) {
        pbVar6 = local_20;
        FUN_0042da60(pbVar6);
        FUN_006cae50(pbVar6);
      }
      iVar4 = FUN_0081dee0();
      iVar4 = iVar4 + -1;
      FUN_0042da60(iVar4);
      FUN_006cf480(iVar4);
      local_34 = FUN_0041f870();
      ~basic_string<>();
    }
  }
  else {
    iVar4 = FUN_0081dee0();
    iVar4 = iVar4 + -1;
    FUN_004305e0(iVar4);
    FUN_006cf480(iVar4);
    FUN_0041f870();
  }
  FUN_0083e885();
  return;
}

