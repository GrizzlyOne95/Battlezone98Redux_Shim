
void FUN_007aaa70(void)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  undefined4 uVar4;
  undefined4 extraout_var;
  char *local_c;
  
  FUN_007cf960();
  uVar4 = extraout_var;
  pcVar3 = (char *)FUN_0041f870();
  pcVar2 = DAT_009181a4;
  local_c = DAT_009181a4;
  do {
    cVar1 = *pcVar3;
    *local_c = cVar1;
    pcVar3 = pcVar3 + 1;
    local_c = local_c + 1;
  } while (cVar1 != '\0');
  uVar4 = FUN_007c3cc0(pcVar2,pcVar3,uVar4);
  *(undefined4 *)(DAT_009181a4 + 0x30) = uVar4;
  uVar4 = FUN_007c3cc0();
  *(undefined4 *)(DAT_009181a4 + 0x34) = uVar4;
  DAT_009181a4[0x38] = '\0';
  FUN_00788f00();
  return;
}

