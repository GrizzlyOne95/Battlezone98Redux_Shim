/*
 * Entry: 0056e8d7
 * Name: GetMissionDesc
 * Namespace: Global
 * Signature: void GetMissionDesc(char * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl GetMissionDesc(char *param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  int iVar4;
  undefined1 auVar5 [4];
  undefined4 *puVar6;
  long lVar7;
  void *pvVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined1 local_10c [4];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)(local_108 + 0x7c);
  local_10c = (undefined1  [4])param_2;
  memset(param_2,0,0x1f400);
  iVar9 = 0;
  iVar4 = -(int)param_1;
  do {
    cVar3 = *param_1;
    param_1[(int)(local_108 + iVar4)] = cVar3;
    if (cVar3 == '.') {
      local_108[iVar9] = '\0';
      break;
    }
    iVar9 = iVar9 + 1;
    param_1 = param_1 + 1;
  } while (iVar9 < 0x100);
  puVar6 = (undefined4 *)(local_10c + 3);
  do {
    puVar10 = puVar6;
    puVar6 = (undefined4 *)((int)puVar10 + 1);
  } while (*(char *)((int)puVar10 + 1) != '\0');
  *(undefined4 *)((int)puVar10 + 1) = 0x7365642e;
  *(undefined1 *)((int)puVar10 + 5) = 0;
  lVar7 = GetItemSize(local_108);
  if (0x1f400 < lVar7) {
    lVar7 = 0x1f400;
  }
  pvVar8 = UseItem(local_108);
  auVar5 = local_10c;
  if (pvVar8 == (void *)0x0) {
    pcVar1 = (char *)((int)local_10c + 4);
    *(undefined4 *)local_10c = 0x44204f4e;
    pcVar2 = (char *)((int)local_10c + 8);
    pcVar1[0] = 'E';
    pcVar1[1] = 'S';
    pcVar1[2] = 'C';
    pcVar1[3] = 'R';
    pcVar2[0] = 'I';
    pcVar2[1] = 'P';
    pcVar2[2] = 'T';
    pcVar2[3] = 'I';
    ((char *)((int)local_10c + 0xc))[0] = 'O';
    ((char *)((int)local_10c + 0xc))[1] = 'N';
    *(char *)((int)local_10c + 0xe) = '\0';
  }
  else {
    memcpy(local_10c,pvVar8,lVar7);
    *(char *)((int)auVar5 + lVar7) = '\0';
    UnlockItem(local_108);
    PurgeItem(local_108);
  }
  return;
}
