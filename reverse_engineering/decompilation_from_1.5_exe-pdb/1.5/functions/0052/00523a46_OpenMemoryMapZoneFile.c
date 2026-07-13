/*
 * Entry: 00523a46
 * Name: OpenMemoryMapZoneFile
 * Namespace: Global
 * Signature: int OpenMemoryMapZoneFile(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl OpenMemoryMapZoneFile(void)

{
  char cVar1;
  undefined4 *puVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  int extraout_EAX;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  undefined4 *puVar7;
  undefined1 local_294 [4];
  char local_290 [4];
  undefined1 auStack_28c [108];
  undefined1 local_220 [147];
  undefined4 uStack_18d;
  undefined1 auStack_188 [256];
  char local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_220;
  iVar3 = 0;
  do {
    cVar1 = missionName[iVar3];
    *(char *)((int)&uStack_18d + iVar3 + 1) = cVar1;
    iVar3 = iVar3 + 1;
  } while (cVar1 != '\0');
  if (uStack_18d._1_1_ != '\0') {
    pcVar4 = strrchr((char *)((int)&uStack_18d + 1),0x2e);
    if (pcVar4 != (char *)0x0) {
      *pcVar4 = '\0';
    }
    puVar2 = &uStack_18d;
    do {
      puVar7 = puVar2;
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = 0x5447482e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    iVar3 = 0;
    do {
      cVar1 = *(char *)((int)&uStack_18d + iVar3 + 1);
      local_88[iVar3] = cVar1;
      iVar3 = iVar3 + 1;
    } while (cVar1 != '\0');
    pcVar4 = strrchr(missionName,0x2e);
    if (pcVar4 != (char *)0x0) {
      *pcVar4 = '\0';
    }
    puVar2 = (undefined4 *)0xca6cbf;
    do {
      puVar7 = puVar2;
      puVar2 = (undefined4 *)((int)puVar7 + 1);
    } while (*(char *)((int)puVar7 + 1) != '\0');
    *(undefined4 *)((int)puVar7 + 1) = 0x4e52542e;
    *(undefined1 *)((int)puVar7 + 5) = 0;
    local_294 = (undefined1  [4])GetINIInt("Size","Width",-1,missionName);
    iVar3 = GetINIInt("Size","Depth",-1,missionName);
    iVar5 = GetINIInt("Size","MinX",-1,missionName);
    iVar6 = GetINIInt("Size","MinZ",-1,missionName);
    if ((((-1 < (int)local_294) && (-1 < iVar3)) && (-1 < iVar5)) && (-1 < iVar6)) {
      _ftol2_sse();
      local_294 = (undefined1  [4])(extraout_EAX >> 7);
      _ftol2_sse();
      iVar3 = extraout_EAX_00 >> 7;
      _ftol2_sse();
      _ftol2_sse();
      memset(ZoneMap,0xff,0x1900);
      nZones = 0;
      if (0 < iVar3) {
        pcVar4 = ZoneMap[extraout_EAX_02 >> 7] + (extraout_EAX_01 >> 7);
        do {
          iVar5 = 0;
          if (0 < (int)local_294) {
            do {
              pcVar4[iVar5] = (char)nZones;
              iVar5 = iVar5 + 1;
              nZones = nZones + 1;
            } while (iVar5 < (int)local_294);
          }
          pcVar4 = pcVar4 + 0x50;
          iVar3 = iVar3 + -1;
        } while (iVar3 != 0);
      }
      iVar3 = 0;
      do {
        pcVar4 = local_88 + iVar3;
        local_290[iVar3] = *pcVar4;
        iVar3 = iVar3 + 1;
      } while (*pcVar4 != '\0');
      pcVar4 = strrchr(local_290,0x2e);
      if (pcVar4 != (char *)0x0) {
        *pcVar4 = '\0';
      }
      puVar2 = (undefined4 *)(local_294 + 3);
      do {
        puVar7 = puVar2;
        puVar2 = (undefined4 *)((int)puVar7 + 1);
      } while (*(char *)((int)puVar7 + 1) != '\0');
      *(undefined4 *)((int)puVar7 + 1) = 0x54414d2e;
      *(undefined1 *)((int)puVar7 + 5) = 0;
      ZoneFileMap.Buffer = zixReadFile(local_88,(int *)&ZoneFileMap.Size);
      MZoneFileMap.Buffer = zixReadFile(local_290,(int *)&MZoneFileMap.Size);
      if ((ZoneFileMap.Buffer != (char *)0x0) && (MZoneFileMap.Buffer != (char *)0x0)) {
        return 1;
      }
    }
  }
  return 0;
}
