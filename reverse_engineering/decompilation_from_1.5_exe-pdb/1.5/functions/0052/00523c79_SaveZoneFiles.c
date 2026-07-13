/*
 * Entry: 00523c79
 * Name: SaveZoneFiles
 * Namespace: Global
 * Signature: int SaveZoneFiles(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl SaveZoneFiles(char *param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  void *lpBuffer;
  HANDLE pvVar4;
  BOOL BVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined1 local_294 [4];
  char local_290 [4];
  undefined1 auStack_28c [116];
  undefined1 local_218 [139];
  undefined4 uStack_18d;
  undefined1 auStack_188 [255];
  undefined4 uStack_89;
  undefined1 auStack_84 [124];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_218;
  zoneDataChanged = 0;
  if ((param_1 == (char *)0x0) || (*param_1 == '\0')) {
    sprintf((char *)((int)&uStack_18d + 1),"Addon\\%s",missionName);
  }
  else {
    iVar6 = 1 - (int)param_1;
    do {
      cVar1 = *param_1;
      param_1[(int)&uStack_18d + iVar6] = cVar1;
      param_1 = param_1 + 1;
    } while (cVar1 != '\0');
    pcVar3 = strrchr((char *)((int)&uStack_18d + 1),0x5c);
    if (pcVar3 == (char *)0x0) {
      pcVar3 = (char *)((int)&uStack_18d + 1);
    }
    pcVar3 = strrchr(pcVar3,0x2e);
    if (pcVar3 != (char *)0x0) {
      *pcVar3 = '\0';
    }
    puVar2 = &uStack_18d;
    do {
      puVar7 = puVar2;
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = 0x4e52542e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    lpBuffer = zixReadFile(missionName,(int *)local_294);
    if (lpBuffer != (void *)0x0) {
      pvVar4 = CreateFileA((LPCSTR)((int)&uStack_18d + 1),0x40000000,3,(LPSECURITY_ATTRIBUTES)0x0,2,
                           0x80,(HANDLE)0x0);
      if (pvVar4 == (HANDLE)0xffffffff) {
        DEBUG_systemWarning("Can\'t open file %s");
      }
      else {
        BVar5 = WriteFile(pvVar4,lpBuffer,(DWORD)local_294,(LPDWORD)local_294,(LPOVERLAPPED)0x0);
        if (BVar5 == 0) {
          DEBUG_systemWarning("Can\'t write file %s");
        }
        CloseHandle(pvVar4);
      }
      zixFree(lpBuffer);
    }
    pcVar3 = strrchr((char *)((int)&uStack_18d + 1),0x5c);
    if (pcVar3 == (char *)0x0) {
      pcVar3 = (char *)((int)&uStack_18d + 1);
    }
    else {
      pcVar3 = pcVar3 + 1;
    }
    TerrainSaveName(pcVar3);
  }
  iVar6 = 0;
  do {
    cVar1 = *(char *)((int)&uStack_18d + iVar6 + 1);
    *(char *)((int)&uStack_89 + iVar6 + 1) = cVar1;
    iVar6 = iVar6 + 1;
  } while (cVar1 != '\0');
  pcVar3 = strrchr((char *)((int)&uStack_89 + 1),0x5c);
  if (pcVar3 == (char *)0x0) {
    pcVar3 = (char *)((int)&uStack_18d + 1);
  }
  pcVar3 = strrchr(pcVar3,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  puVar2 = &uStack_89;
  do {
    puVar7 = puVar2;
    puVar2 = (undefined4 *)((int)puVar7 + 1);
  } while (*(char *)((int)puVar7 + 1) != '\0');
  *(undefined4 *)((int)puVar7 + 1) = 0x5447482e;
  *(undefined1 *)((int)puVar7 + 5) = 0;
  iVar6 = 0;
  do {
    cVar1 = *(char *)((int)&uStack_89 + iVar6 + 1);
    local_290[iVar6] = cVar1;
    iVar6 = iVar6 + 1;
  } while (cVar1 != '\0');
  pcVar3 = strrchr(local_290,0x5c);
  if (pcVar3 == (char *)0x0) {
    pcVar3 = (char *)((int)&uStack_18d + 1);
  }
  pcVar3 = strrchr(pcVar3,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  puVar2 = (undefined4 *)(local_294 + 3);
  do {
    puVar7 = puVar2;
    puVar2 = (undefined4 *)((int)puVar7 + 1);
  } while (*(char *)((int)puVar7 + 1) != '\0');
  *(undefined4 *)((int)puVar7 + 1) = 0x54414d2e;
  *(undefined1 *)((int)puVar7 + 5) = 0;
  pvVar4 = CreateFileA((LPCSTR)((int)&uStack_89 + 1),0x40000000,3,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,
                       (HANDLE)0x0);
  if (pvVar4 == (HANDLE)0xffffffff) {
    DEBUG_systemWarning("Can\'t open file %s");
  }
  else {
    BVar5 = WriteFile(pvVar4,ZoneFileMap.Buffer,ZoneFileMap.Size,(LPDWORD)local_294,
                      (LPOVERLAPPED)0x0);
    if (BVar5 == 0) {
      DEBUG_systemWarning("Can\'t write file %s");
    }
    CloseHandle(pvVar4);
  }
  pvVar4 = CreateFileA(local_290,0x40000000,3,(LPSECURITY_ATTRIBUTES)0x0,2,0x80,(HANDLE)0x0);
  if (pvVar4 == (HANDLE)0xffffffff) {
    DEBUG_systemWarning("Can\'t open file %s");
  }
  else {
    BVar5 = WriteFile(pvVar4,MZoneFileMap.Buffer,MZoneFileMap.Size,(LPDWORD)local_294,
                      (LPOVERLAPPED)0x0);
    if (BVar5 == 0) {
      DEBUG_systemWarning("Can\'t write file %s");
    }
    CloseHandle(pvVar4);
  }
  return 1;
}
