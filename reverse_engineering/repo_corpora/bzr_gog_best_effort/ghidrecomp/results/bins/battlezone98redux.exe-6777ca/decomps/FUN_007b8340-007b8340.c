
void FUN_007b8340(void)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 extraout_var;
  
  FUN_007cf960();
  uVar4 = extraout_var;
  pcVar2 = (char *)FUN_0041f870();
  pcVar6 = DAT_009181a8;
  pcVar5 = DAT_009181a8;
  do {
    cVar1 = *pcVar2;
    *pcVar5 = cVar1;
    pcVar2 = pcVar2 + 1;
    pcVar5 = pcVar5 + 1;
  } while (cVar1 != '\0');
  iVar3 = FUN_007c3cc0(pcVar6,pcVar2,pcVar5,uVar4);
  DAT_009181a8[0x28] = iVar3 != 0;
  iVar3 = FUN_007c3cc0(pcVar6,pcVar2,pcVar5,uVar4);
  DAT_009181a8[0x29] = iVar3 != 0;
  iVar3 = FUN_007c3cc0(pcVar6,pcVar2,pcVar5,uVar4);
  DAT_009181a8[0x2a] = iVar3 != 0;
  iVar3 = FUN_007c3cc0(pcVar6);
  DAT_009181a8[0x34] = iVar3 != 0;
  uVar4 = FUN_007c48b0();
  *(undefined4 *)(DAT_009181a8 + 0x2c) = uVar4;
  uVar4 = FUN_007c48b0();
  *(undefined4 *)(DAT_009181a8 + 0x30) = uVar4;
  DAT_009181a8[0x35] = '\0';
  FUN_00788f00();
  return;
}

