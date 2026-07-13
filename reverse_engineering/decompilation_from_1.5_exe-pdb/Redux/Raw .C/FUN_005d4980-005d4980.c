
void __fastcall FUN_005d4980(undefined4 param_1)

{
  undefined4 uVar1;
  char *pcVar2;
  
  if (DAT_00918320 == 0) {
    FUN_0081e820("Starting loading game UI wrapper\n",param_1);
    uVar1 = FUN_0081e660();
    FUN_004bc590(uVar1);
    FUN_004fc490(&DAT_00945708,1);
    uVar1 = FUN_00572a70(&DAT_00915540);
    FUN_007647c0(uVar1);
    FUN_0078bb00();
    DAT_00918328 = 0x17;
    DAT_009455df = 0;
    while ((DAT_00918328 != 0 && (DAT_009455de == '\0'))) {
      DAT_009455df = 0;
      FUN_005d5150(DAT_00918328);
    }
    DAT_00918328 = 0;
    if (DAT_00918320 == 0) {
      pcVar2 = "\n";
    }
    else {
      pcVar2 = " (parent still set)\n";
    }
    FUN_0081e820("Ending loading game UI wrapper",pcVar2);
    uVar1 = FUN_0081e660();
    uVar1 = FUN_004bc590(uVar1);
    FUN_004bc590(uVar1);
  }
  return;
}

