
void FUN_00836e87(undefined4 param_1)

{
  char cVar1;
  FILE *pFVar2;
  char *pcVar3;
  int iVar4;
  char local_104 [252];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  pFVar2 = __iob_func();
  fputs("lua_debug> ",pFVar2 + 2);
  pFVar2 = __iob_func();
  pcVar3 = fgets(local_104,0xfa,pFVar2);
  while (pcVar3 != (char *)0x0) {
    iVar4 = memcmp(local_104,"cont\n",6);
    if (iVar4 == 0) break;
    pcVar3 = local_104;
    do {
      cVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
    } while (cVar1 != '\0');
    iVar4 = FUN_0082be6f(param_1,local_104,(int)pcVar3 - (int)(local_104 + 1),"=(debug command)");
    if (iVar4 == 0) {
      iVar4 = FUN_0082cb8c(param_1,0,0,0);
      if (iVar4 != 0) goto LAB_00836f30;
    }
    else {
LAB_00836f30:
      pFVar2 = __iob_func();
      pFVar2 = pFVar2 + 2;
      pcVar3 = (char *)FUN_0082d377(param_1,0xffffffff,0);
      fputs(pcVar3,pFVar2);
      pFVar2 = __iob_func();
      fputs("\n",pFVar2 + 2);
    }
    FUN_0082d226(param_1,0);
    pFVar2 = __iob_func();
    fputs("lua_debug> ",pFVar2 + 2);
    pFVar2 = __iob_func();
    pcVar3 = fgets(local_104,0xfa,pFVar2);
  }
  FUN_0083e885();
  return;
}

