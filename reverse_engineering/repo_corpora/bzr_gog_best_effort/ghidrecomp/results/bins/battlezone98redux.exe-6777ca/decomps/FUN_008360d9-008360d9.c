
byte * FUN_008360d9(undefined4 param_1,byte *param_2,undefined1 *param_3)

{
  byte bVar1;
  byte *pbVar2;
  char *pcVar3;
  int iVar4;
  byte *pbVar5;
  
  bVar1 = *param_2;
  pbVar5 = param_2;
  while ((bVar1 != 0 && (pcVar3 = strchr("-+ #0",(int)(char)*pbVar5), pcVar3 != (char *)0x0))) {
    pbVar5 = pbVar5 + 1;
    bVar1 = *pbVar5;
  }
  if (5 < (uint)((int)pbVar5 - (int)param_2)) {
    FUN_0082bc39(param_1,"invalid format (repeated flags)");
  }
  iVar4 = isdigit((uint)*pbVar5);
  if (iVar4 != 0) {
    pbVar5 = pbVar5 + 1;
  }
  iVar4 = isdigit((uint)*pbVar5);
  if (iVar4 != 0) {
    pbVar5 = pbVar5 + 1;
  }
  if (*pbVar5 == 0x2e) {
    iVar4 = isdigit((uint)pbVar5[1]);
    pbVar2 = pbVar5 + 1;
    if (iVar4 != 0) {
      pbVar2 = pbVar5 + 2;
    }
    pbVar5 = pbVar2;
    iVar4 = isdigit((uint)*pbVar5);
    if (iVar4 != 0) {
      pbVar5 = pbVar5 + 1;
    }
  }
  iVar4 = isdigit((uint)*pbVar5);
  if (iVar4 != 0) {
    FUN_0082bc39(param_1,"invalid format (width or precision too long)");
  }
  *param_3 = 0x25;
  strncpy(param_3 + 1,(char *)param_2,(size_t)(pbVar5 + (1 - (int)param_2)));
  (param_3 + 1)[(int)(pbVar5 + (1 - (int)param_2))] = '\0';
  return pbVar5;
}

