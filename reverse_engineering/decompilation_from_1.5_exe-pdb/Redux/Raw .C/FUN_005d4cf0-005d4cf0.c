
void __fastcall FUN_005d4cf0(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  char *pcVar3;
  
  if (DAT_0091832c == 0) {
    FUN_0081e820("Starting fail game UI wrapper\n",param_1);
    uVar1 = FUN_0081e660();
    FUN_004bc590(uVar1);
    FUN_00434600();
    FUN_00822a70();
    FUN_0043a570();
    FUN_00623ff0();
    DAT_00918328 = 0x13;
    while ((DAT_00918328 != 0 && (DAT_009455de == '\0'))) {
      DAT_009455df = 0;
      FUN_005d5150(DAT_00918328);
    }
    DAT_00918328 = 0;
    FUN_0043a910(0xffffffff,0xffffffff,0xffffffff);
    iVar2 = FUN_00434160();
    if (iVar2 == 5) {
      FUN_0043a5f0();
    }
    FUN_00822ab0();
    FUN_00434600();
    FUN_00623eb0();
    if (DAT_00918320 == 0) {
      pcVar3 = "\n";
    }
    else {
      pcVar3 = " (parent still set)\n";
    }
    FUN_0081e820("Ending fail game UI wrapper",pcVar3);
    uVar1 = FUN_0081e660();
    uVar1 = FUN_004bc590(uVar1);
    FUN_004bc590(uVar1);
  }
  return;
}

