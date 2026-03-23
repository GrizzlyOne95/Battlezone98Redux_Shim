
void __thiscall FUN_005d4690(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  basic_ostream<char,struct_std::char_traits<char>_> *pbVar2;
  int iVar3;
  code *pcVar4;
  char *pcVar5;
  
  if ((DAT_0091832c == 0) && (DAT_0091812b == '\0')) {
    pcVar4 = FUN_004bc8c0;
    iVar3 = param_2;
    FUN_0081e820("Starting escape/in game UI wrapper with dialog ",param_2,FUN_004bc8c0,param_1);
    uVar1 = FUN_0081e660();
    pbVar2 = (basic_ostream<char,struct_std::char_traits<char>_> *)FUN_004bc590(uVar1);
    pbVar2 = std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,iVar3);
    std::basic_ostream<char,struct_std::char_traits<char>_>::operator<<(pbVar2,pcVar4);
    FUN_005d50f0();
    DAT_0091812b = '\x01';
    (*(code *)PTR_FUN_008e75e8)();
    FUN_00621590();
    DAT_0091989c = 0;
    FUN_00623ff0();
    FUN_00434600();
    FUN_0067ca70(0,0,0);
    iVar3 = (*DAT_02cecf6c)(&DAT_02cecee0);
    if (iVar3 == 0) {
      FUN_007d6c70("BattleZone Init_Graphic_System");
    }
    FUN_00434600();
    iVar3 = FUN_00572a70();
    if (iVar3 == 0) {
      FUN_00822a70();
    }
    FUN_00437bc0();
    DAT_00918328 = param_2;
    DAT_00918310 = 1;
    DAT_009455df = '\0';
    while (((DAT_00918328 != 0 && (DAT_009455de == '\0')) && (DAT_009455df == '\0'))) {
      FUN_005d5150(DAT_00918328);
    }
    DAT_00918328 = 0;
    DAT_00918310 = 0;
    (*(code *)PTR_FUN_008e75e8)();
    FUN_00621010();
    FUN_00434f20();
    iVar3 = FUN_00434160();
    if (iVar3 == 5) {
      FUN_0043a910(0xffffffff,0xffffffff,0xffffffff);
      FUN_00437bd0();
      FUN_004378f0();
      iVar3 = FUN_00572a70();
      if (iVar3 == 0) {
        FUN_00822ab0();
      }
      FUN_00434600();
      iVar3 = (*DAT_02cecf6c)(&DAT_02cecee0);
      if (iVar3 == 0) {
        FUN_007d6c70("BattleZone Init_Graphic_System");
      }
      FUN_00434600();
      FUN_004375d0(&DAT_02cecee0);
      FUN_00623eb0();
      DAT_0091812b = '\0';
      (*(code *)PTR_FUN_008e75e8)();
      if (DAT_00918320 == 0) {
        pcVar5 = "\n";
      }
      else {
        pcVar5 = " (parent still set)\n";
      }
      FUN_0081e820("Ending escape/in game UI wrapper",pcVar5);
      uVar1 = FUN_0081e660();
      uVar1 = FUN_004bc590(uVar1);
      FUN_004bc590(uVar1);
    }
    else {
      DAT_0091812b = '\0';
    }
  }
  return;
}

