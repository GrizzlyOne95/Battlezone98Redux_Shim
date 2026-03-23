
undefined4 __thiscall
FUN_006a0560(undefined4 param_1,undefined2 param_2,undefined2 param_3,undefined1 param_4)

{
  char cVar1;
  short *psVar2;
  
  psVar2 = (short *)FUN_0069fe90(param_3,param_1);
  while( true ) {
    if (*psVar2 == 0) {
      return 0;
    }
    cVar1 = FUN_006a0230(*psVar2,param_4,param_2);
    if (cVar1 != '\0') break;
    psVar2 = psVar2 + 1;
  }
  return 1;
}

