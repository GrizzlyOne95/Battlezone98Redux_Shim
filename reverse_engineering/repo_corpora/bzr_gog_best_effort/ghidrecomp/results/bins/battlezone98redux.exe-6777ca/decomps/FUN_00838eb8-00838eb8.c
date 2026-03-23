
void FUN_00838eb8(undefined4 param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  
  iVar5 = 0;
  do {
    pcVar2 = (&PTR_DAT_00870350)[iVar5];
    pcVar4 = pcVar2;
    do {
      cVar1 = *pcVar4;
      pcVar4 = pcVar4 + 1;
    } while (cVar1 != '\0');
    iVar3 = FUN_008309f4(param_1,pcVar2,(int)pcVar4 - (int)(pcVar2 + 1));
    cVar1 = (char)iVar5;
    *(byte *)(iVar3 + 5) = *(byte *)(iVar3 + 5) | 0x20;
    iVar5 = iVar5 + 1;
    *(char *)(iVar3 + 6) = cVar1 + '\x01';
  } while (iVar5 < 0x15);
  return;
}

