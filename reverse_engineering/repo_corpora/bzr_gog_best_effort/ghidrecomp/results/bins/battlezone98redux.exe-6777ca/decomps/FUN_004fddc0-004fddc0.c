
void FUN_004fddc0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  char *local_74;
  char *local_70;
  undefined1 local_68 [24];
  undefined1 local_50 [48];
  basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_> local_20 [24];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((0 < param_1) && (param_1 < 0xb)) {
    FUN_00426a60(&DAT_02ceefe0,0);
    basic_string<>(&DAT_0087bb64);
    uVar2 = FUN_00482630(local_68,param_1);
    FUN_00449810(uVar2);
    ~basic_string<>();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_20,".sav");
    FUN_004fed70(local_20);
    DAT_009467b4 = 0;
    FUN_00417fd0(local_50);
    local_74 = (char *)FUN_0041f870();
    local_70 = &DAT_00945708;
    puVar3 = &DAT_00945708;
    do {
      cVar1 = *local_74;
      *local_70 = cVar1;
      local_74 = local_74 + 1;
      local_70 = local_70 + 1;
    } while (cVar1 != '\0');
    ~basic_string<>(&DAT_00945708);
    FUN_0081e0c0("Load Game: Run state set to bookmark\n");
    FUN_00434170(8);
    FUN_004fc490(&DAT_00945708,1);
    uVar2 = FUN_00572a70(&DAT_00915540);
    FUN_007647c0(uVar2);
    ~basic_string<>(puVar3,1);
    FUN_004180b0();
  }
  FUN_0083e885();
  return;
}

