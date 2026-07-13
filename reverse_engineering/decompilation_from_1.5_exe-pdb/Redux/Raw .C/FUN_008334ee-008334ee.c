
void FUN_008334ee(int param_1)

{
  char *pcVar1;
  byte *pbVar2;
  int *piVar3;
  char cVar4;
  undefined4 uVar5;
  char *pcVar6;
  int iVar7;
  
  iVar7 = 0xbc;
  do {
    pcVar6 = *(char **)("get length of" + iVar7 + 4);
    pcVar1 = pcVar6 + 1;
    do {
      cVar4 = *pcVar6;
      pcVar6 = pcVar6 + 1;
    } while (cVar4 != '\0');
    uVar5 = FUN_008309f4(param_1,*(undefined4 *)("get length of" + iVar7 + 4),
                         (int)pcVar6 - (int)pcVar1);
    *(undefined4 *)(iVar7 + *(int *)(param_1 + 0x10)) = uVar5;
    piVar3 = (int *)(*(int *)(param_1 + 0x10) + iVar7);
    iVar7 = iVar7 + 4;
    pbVar2 = (byte *)(*piVar3 + 5);
    *pbVar2 = *pbVar2 | 0x20;
  } while (iVar7 < 0x100);
  return;
}

