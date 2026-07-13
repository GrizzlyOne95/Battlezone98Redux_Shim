
void FUN_00616fc0(void)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_00572a70(&DAT_00915540);
  FUN_007647c0(uVar1);
  FUN_0081e0c0("Starting Game Simulator\n");
  FUN_0043d1a0(1);
  FUN_00822830();
  FUN_0081e0c0("Initializing Game Simulator\n");
  FUN_00822ef0();
  FUN_0041e840();
  FUN_00621010();
  FUN_006217a0();
  FUN_0062d5a0();
  FUN_0062c280();
  FUN_008210f0();
  FUN_008231b0();
  if (DAT_0091556c == 0) {
    iVar2 = (*DAT_02cecf6c)(&DAT_02cecee0);
    if (iVar2 == 0) {
      FUN_007d6c70("BattleZone Init_Graphic_System");
    }
    FUN_00618bc0();
    FUN_00437620(2);
    DAT_00915550 = 1;
  }
  FUN_0077d450();
  FUN_004e3250();
  FUN_0062a240();
  FUN_0068b0e0();
  FUN_00442980();
  FUN_0062b7f0();
  FUN_004b6eb0();
  FUN_0045bef0();
  FUN_004d4350();
  FUN_0049af40();
  return;
}

