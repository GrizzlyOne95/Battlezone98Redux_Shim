
void FUN_004fdc80(int param_1,char *param_2)

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
  local_74 = param_2;
  local_70 = &DAT_008e86d8;
  puVar3 = &DAT_008e86d8;
  do {
    cVar1 = *local_74;
    *local_70 = cVar1;
    local_74 = local_74 + 1;
    local_70 = local_70 + 1;
  } while (cVar1 != '\0');
  if ((0 < param_1) && (param_1 < 0xb)) {
    FUN_00426a60(&DAT_02ceefe0,0);
    basic_string<>(&DAT_0087bb64);
    uVar2 = FUN_00482630(local_68,param_1);
    FUN_00449810(uVar2);
    ~basic_string<>();
    std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>::operator=
              (local_20,".sav");
    FUN_004fed70(local_20);
    DAT_009173b7 = 0;
    DAT_009173b6 = DAT_008eaab4 != 0;
    uVar2 = 0;
    FUN_00417fd0(local_50);
    uVar2 = FUN_0041f870(uVar2);
    uVar2 = FUN_004fd190(uVar2);
    ~basic_string<>(puVar3,uVar2);
    DAT_009173b6 = 0;
    ~basic_string<>(puVar3,uVar2,uVar2);
    FUN_004180b0();
  }
  FUN_0083e885();
  return;
}

