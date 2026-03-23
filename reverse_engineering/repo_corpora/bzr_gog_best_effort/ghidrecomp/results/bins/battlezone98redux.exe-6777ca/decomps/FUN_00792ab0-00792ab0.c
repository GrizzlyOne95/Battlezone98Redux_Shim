
void __fastcall FUN_00792ab0(int param_1)

{
  int iVar1;
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *pbVar2;
  int iVar3;
  void *pvVar4;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 uStack_44;
  char *pcStack_40;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085ef8c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00482850();
  pcStack_40 = (char *)0x792ae3;
  iVar1 = FUN_004888b0();
  pbVar2 = (basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
           FUN_00482850();
  std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>
            ((basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> *)
             &local_50,pbVar2);
  iVar3 = FUN_004885d0();
  if ((iVar1 < 0) || (iVar1 + 1 != iVar3)) {
    pcStack_40 = (char *)0x792c45;
    FUN_0081e0c0();
    pcStack_40 = (char *)0x792c4f;
    FUN_00434170();
    pcStack_40 = (char *)0x792c62;
    FUN_007c9170();
    DAT_00918328 = 0;
  }
  else {
    FUN_00793070();
    pcStack_40 = (char *)0x792b3c;
    pvVar4 = operator_new(0x144);
    local_8 = 0;
    if (pvVar4 == (void *)0x0) {
      local_20 = 0;
    }
    else {
      uStack_44 = 0x101;
      local_48 = 0x44870000;
      local_4c = 0x44f00000;
      local_50 = 0;
      pcStack_40 = (char *)param_1;
      local_20 = FUN_007d1cc0("movie",0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x14c) = local_20;
    pcStack_40 = (char *)0x792be0;
    FUN_007d3f20();
    pcStack_40 = "j";
    FUN_0078c480();
    pcStack_40 = "credits.ogv";
    uStack_44 = 0x792c05;
    FUN_007d3850();
    pcStack_40 = "j";
    FUN_007d3dd0();
    pcStack_40 = *(char **)(param_1 + 0x14c);
    uStack_44 = 0x792c2f;
    FUN_007d2110();
    *(undefined1 *)(param_1 + 0x15c) = 1;
  }
  ExceptionList = local_10;
  return;
}

