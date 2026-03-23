
void FUN_0082d51d(undefined4 param_1)

{
  code *pcVar1;
  undefined **ppuVar2;
  
  pcVar1 = FUN_00834525;
  ppuVar2 = &PTR_DAT_0086eb98;
  while (pcVar1 != (code *)0x0) {
    FUN_0082cc15(param_1,pcVar1,0);
    FUN_0082cd77(param_1,*ppuVar2);
    FUN_0082c585(param_1,1,0);
    pcVar1 = (code *)ppuVar2[3];
    ppuVar2 = ppuVar2 + 2;
  }
  return;
}

