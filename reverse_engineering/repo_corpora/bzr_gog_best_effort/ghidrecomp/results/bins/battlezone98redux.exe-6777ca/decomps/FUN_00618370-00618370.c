
void __fastcall FUN_00618370(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  if ((DAT_009454b8 != 0) && (DAT_009454a4 != 0)) {
    DAT_009454a4 = 0;
    DAT_009454ac = 0;
    FUN_005b0920(0,param_1);
    FUN_00780800(0);
    *(uint *)(DAT_0094672c + 0x30) = *(uint *)(DAT_0094672c + 0x30) & 0xfffffffe;
  }
  FUN_00820b90();
  iVar1 = FUN_00434160();
  FUN_00437a70();
  FUN_0067ca70(0,0,0);
  if (iVar1 == 1) {
    FUN_005d4de0();
  }
  else if ((iVar1 == 0) || (iVar1 == 10)) {
    FUN_005d4cf0();
  }
  FUN_0043a020();
  iVar2 = FUN_00572a70();
  if (iVar2 != 0) {
    FUN_00570460();
  }
  FUN_0062b810();
  FUN_00623ff0();
  FUN_00621590();
  FUN_00822ee0();
  FUN_00780c00();
  FUN_0068a2b0();
  FUN_004b6ee0();
  FUN_006152b0();
  FUN_0077d510();
  FUN_00629fe0();
  FUN_0062b8a0();
  FUN_0049b380();
  FUN_004dfbb0();
  FUN_005c5a10();
  FUN_00584e60();
  FUN_004d4770();
  FUN_004df9b0();
  FUN_00611160();
  FUN_00780c40();
  FUN_0043a060();
  FUN_0043d1a0(0);
  FUN_0062c330();
  FUN_00442e10();
  FUN_0045c030();
  FUN_004d4820();
  FUN_004cbae0();
  FUN_00587140();
  FUN_00612240();
  FUN_004e1b20();
  FUN_0062d5a0();
  FUN_004e36f0();
  FUN_0062cc80();
  iVar2 = FUN_00572a70();
  if (iVar2 != 0) {
    CPngImage::CleanUp();
  }
  FUN_00824030();
  FUN_00821a80();
  if ((((DAT_0091556c == 0) && (iVar1 != 6)) && (iVar1 != 9)) && (iVar1 != 8)) {
    FUN_00820fb0();
    FUN_008205e0();
  }
  FUN_0067d0c0();
  FUN_006839b0();
  return;
}

