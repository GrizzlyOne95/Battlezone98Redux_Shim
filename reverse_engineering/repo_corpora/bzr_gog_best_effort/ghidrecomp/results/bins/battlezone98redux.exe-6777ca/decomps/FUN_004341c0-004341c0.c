
undefined4 FUN_004341c0(void)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_1c;
  char *local_18;
  char *local_14;
  char *local_10;
  
  iVar2 = FUN_00434160();
  if (((iVar2 == 5) || (iVar2 == 2)) && (DAT_0091556c == 0)) {
    FUN_00618bc0();
    iVar2 = (*DAT_02cecf6c)(&DAT_02cecee0);
    if (iVar2 == 0) {
      FUN_007d6c70("BattleZone Init_Graphic_System");
    }
    iVar2 = FUN_00434160();
    if (iVar2 != 9) {
      FUN_00618bc0();
      FUN_0067ca70(0,0,0);
      FUN_004377c0(DAT_008e772c,DAT_008e772c,0xffffffff,DAT_008e772c);
      FUN_004378f0();
      FUN_005d42e0();
      FUN_00437a70();
      FUN_00618bc0();
    }
  }
  iVar2 = FUN_00434160();
  if ((iVar2 == 9) || ((iVar2 == 2 && (DAT_0091556c != 0)))) {
    CPngImage::CleanUp();
    FUN_005d50f0();
    FUN_00623ff0();
    uVar3 = 0;
  }
  else {
    if (iVar2 == 6) {
      local_18 = &DAT_00915540;
      local_10 = &DAT_00945708;
      do {
        cVar1 = *local_18;
        *local_10 = cVar1;
        local_18 = local_18 + 1;
        local_10 = local_10 + 1;
      } while (cVar1 != '\0');
      FUN_005d4980();
      FUN_00434170(5);
    }
    else if (iVar2 == 8) {
      FUN_004fdfe0(&DAT_00945708,&DAT_00915540,0x10);
      FUN_005d4980();
      FUN_00434170(5);
    }
    else if (iVar2 == 5) {
      local_1c = &DAT_00915540;
      local_14 = &DAT_00945708;
      do {
        cVar1 = *local_1c;
        *local_14 = cVar1;
        local_1c = local_1c + 1;
        local_14 = local_14 + 1;
      } while (cVar1 != '\0');
      FUN_005d4980(&DAT_00945708);
    }
    uVar3 = 1;
  }
  return uVar3;
}

