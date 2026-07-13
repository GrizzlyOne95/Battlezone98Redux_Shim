/*
 * Entry: 00504998
 * Name: GetWin9xDisplayInfo
 * Namespace: Global
 * Signature: void GetWin9xDisplayInfo(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl GetWin9xDisplayInfo(void)

{
  BYTE *pBVar1;
  LPBYTE lpData;
  char cVar2;
  BYTE BVar3;
  LSTATUS LVar4;
  BYTE *pBVar5;
  char *pcVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  char *pcVar10;
  BYTE *pBVar11;
  BYTE *pBVar12;
  DWORD local_3ab4;
  DWORD local_3ab0;
  DWORD local_3aac;
  BYTE *local_3aa8;
  undefined4 *local_3aa4;
  BYTE *local_3aa0;
  int local_3a9c;
  HKEY local_3a98;
  HKEY local_3a94;
  HKEY local_3a90;
  BYTE *local_3a8c;
  DWORD local_3a88;
  BYTE local_3a84 [80];
  undefined1 local_3a34 [4016];
  BYTE aBStack_2a84 [4096];
  char local_1a84 [1024];
  BYTE aBStack_1684 [4095];
  char cStack_685;
  char local_684 [1024];
  CHAR local_284 [255];
  BYTE BStack_185;
  BYTE local_184 [256];
  BYTE local_84 [64];
  undefined4 local_44;
  undefined1 uStack_40;
  undefined4 local_3f;
  undefined4 uStack_3b;
  undefined4 uStack_37;
  undefined2 uStack_33;
  undefined1 uStack_31;
  undefined4 local_30;
  undefined2 uStack_2c;
  undefined1 uStack_2a;
  undefined4 local_29;
  undefined4 uStack_25;
  undefined4 uStack_21;
  undefined1 uStack_1d;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined4 uStack_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_3a34;
  local_44 = 0x534f4942;
  uStack_40 = 0;
  local_3f = 0;
  uStack_3b = 0;
  uStack_37 = 0;
  uStack_33 = 0;
  uStack_31 = 0;
  local_30 = 0x50415349;
  uStack_2c = 0x504e;
  uStack_2a = 0;
  local_29 = 0;
  uStack_25 = 0;
  uStack_21 = 0;
  local_3a9c = -1;
  uStack_1d = 0;
  local_1c = 0x494350;
  local_18 = 0;
  uStack_14 = 0;
  uStack_10 = 0;
  uStack_c = 0;
  memset(local_3a84,0,0x1000);
  local_3aa4 = &local_44;
  useHalfTexel = 0;
  local_3aa8 = (BYTE *)0x3;
  do {
    local_3a90 = (HKEY)0x0;
    sprintf(local_684,"Enum\\%s",local_3aa4);
    LVar4 = RegOpenKeyExA((HKEY)0x80000002,local_684,0,0x20019,&local_3a90);
    if (LVar4 == 0) {
      local_3ab0 = 0;
      while( true ) {
        local_3a88 = 0x100;
        LVar4 = RegEnumKeyExA(local_3a90,local_3ab0,(LPSTR)local_184,&local_3a88,(LPDWORD)0x0,
                              (LPSTR)0x0,(LPDWORD)0x0,(PFILETIME)0x0);
        if (LVar4 != 0) break;
        local_3a98 = (HKEY)0x0;
        sprintf(local_684,"Enum\\%s\\%s",local_3aa4,local_184);
        LVar4 = RegOpenKeyExA((HKEY)0x80000002,local_684,0,0x20019,&local_3a98);
        if (LVar4 == 0) {
          local_3a88 = 0x100;
          local_3ab4 = 0;
          LVar4 = RegEnumKeyExA(local_3a98,0,local_284,&local_3a88,(LPDWORD)0x0,(LPSTR)0x0,
                                (LPDWORD)0x0,(PFILETIME)0x0);
          if (LVar4 == 0) {
            local_3a8c = local_3a84 + local_3a9c * 0x100;
            local_3aa0 = aBStack_1684 + local_3a9c * 0x100;
            do {
              local_3a94 = (HKEY)0x0;
              pcVar6 = &cStack_685;
              do {
                pcVar10 = pcVar6 + 1;
                pcVar6 = pcVar6 + 1;
              } while (*pcVar10 != '\0');
              *(char (*) [2])pcVar6 = (char  [2])0x5c;
              pcVar6 = local_284;
              do {
                cVar2 = *pcVar6;
                pcVar6 = pcVar6 + 1;
              } while (cVar2 != '\0');
              uVar9 = (int)pcVar6 - (int)local_284;
              pcVar6 = &cStack_685;
              do {
                pcVar10 = pcVar6 + 1;
                pcVar6 = pcVar6 + 1;
              } while (*pcVar10 != '\0');
              pcVar10 = local_284;
              for (uVar7 = uVar9 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
                *(undefined4 *)pcVar6 = *(undefined4 *)pcVar10;
                pcVar10 = pcVar10 + 4;
                pcVar6 = pcVar6 + 4;
              }
              for (uVar9 = uVar9 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
                *pcVar6 = *pcVar10;
                pcVar10 = pcVar10 + 1;
                pcVar6 = pcVar6 + 1;
              }
              LVar4 = RegOpenKeyExA((HKEY)0x80000002,local_684,0,0x20019,&local_3a94);
              if (LVar4 == 0) {
                local_3a88 = 0x40;
                local_84[0] = '\0';
                LVar4 = RegQueryValueExA(local_3a94,"Class",(LPDWORD)0x0,&local_3aac,local_84,
                                         &local_3a88);
                if ((LVar4 == 0) && (iVar8 = _stricmp((char *)local_84,"DISPLAY"), iVar8 == 0)) {
                  local_3a9c = local_3a9c + 1;
                  local_3aa0 = local_3aa0 + 0x100;
                  local_3a8c = local_3a8c + 0x100;
                  local_3a88 = 0x100;
                  sprintf(local_1a84,"%s\\%s\\%s",local_3aa4,local_184,local_284);
                  LVar4 = RegQueryValueExA(local_3a94,"Driver",(LPDWORD)0x0,&local_3aac,local_3a8c,
                                           &local_3a88);
                  if ((LVar4 == 0) && (*local_3a8c != '\0')) {
                    local_3a88 = 0x100;
                    RegQueryValueExA(local_3a94,"Mfg",(LPDWORD)0x0,&local_3aac,local_3aa0,
                                     &local_3a88);
                  }
                  else {
                    local_3a9c = local_3a9c + -1;
                    local_3aa0 = local_3aa0 + -0x100;
                    *local_3a8c = '\0';
                    local_3a8c = local_3a8c + -0x100;
                  }
                }
              }
              if (local_3a94 != (HKEY)0x0) {
                RegCloseKey(local_3a94);
                local_3a94 = (HKEY)0x0;
              }
              local_3ab4 = local_3ab4 + 1;
              local_3a88 = 0x100;
              LVar4 = RegEnumKeyExA(local_3a98,local_3ab4,local_284,&local_3a88,(LPDWORD)0x0,
                                    (LPSTR)0x0,(LPDWORD)0x0,(PFILETIME)0x0);
            } while (LVar4 == 0);
          }
        }
        if (local_3a98 != (HKEY)0x0) {
          RegCloseKey(local_3a98);
          local_3a98 = (HKEY)0x0;
        }
        local_3ab0 = local_3ab0 + 1;
      }
    }
    if (local_3a90 != (HKEY)0x0) {
      RegCloseKey(local_3a90);
    }
    local_3aa4 = local_3aa4 + 5;
    local_3aa8 = (BYTE *)((int)local_3aa8 + -1);
  } while (local_3aa8 != (BYTE *)0x0);
  local_3a8c = (BYTE *)0x0;
  local_3aa8 = (BYTE *)0x0;
  do {
    pBVar1 = local_3a84 + (int)local_3a8c;
    if (*pBVar1 == '\0') {
      return;
    }
    pBVar5 = (BYTE *)"System\\CurrentControlSet\\Services\\Class\\";
    pBVar12 = local_184;
    for (iVar8 = 10; iVar8 != 0; iVar8 = iVar8 + -1) {
      *(undefined4 *)pBVar12 = *(undefined4 *)pBVar5;
      pBVar5 = pBVar5 + 4;
      pBVar12 = pBVar12 + 4;
    }
    local_3a90 = (HKEY)0x0;
    *pBVar12 = *pBVar5;
    pBVar5 = pBVar1;
    do {
      BVar3 = *pBVar5;
      pBVar5 = pBVar5 + 1;
    } while (BVar3 != '\0');
    pBVar12 = &BStack_185;
    do {
      pBVar11 = pBVar12 + 1;
      pBVar12 = pBVar12 + 1;
    } while (*pBVar11 != '\0');
    pBVar11 = pBVar1;
    for (uVar9 = (uint)((int)pBVar5 - (int)pBVar1) >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
      *(undefined4 *)pBVar12 = *(undefined4 *)pBVar11;
      pBVar11 = pBVar11 + 4;
      pBVar12 = pBVar12 + 4;
    }
    for (uVar9 = (int)pBVar5 - (int)pBVar1 & 3; uVar9 != 0; uVar9 = uVar9 - 1) {
      *pBVar12 = *pBVar11;
      pBVar11 = pBVar11 + 1;
      pBVar12 = pBVar12 + 1;
    }
    LVar4 = RegOpenKeyExA((HKEY)0x80000002,(LPCSTR)local_184,0,0x20019,&local_3a90);
    pBVar1 = local_3a8c;
    if (LVar4 == 0) {
      lpData = aBStack_2a84 + (int)local_3a8c;
      local_3a88 = 0x100;
      RegQueryValueExA(local_3a90,"DriverDesc",(LPDWORD)0x0,&local_3aac,lpData,&local_3a88);
      Trace("DriverDesc: %s\n");
      local_3aa8 = aBStack_1684 + (int)pBVar1;
      Trace("       Mfg: %s\n");
      _strupr((char *)lpData);
      _strupr((char *)local_3aa8);
      pcVar6 = strstr((char *)lpData,"NVIDIA");
      if ((((pcVar6 != (char *)0x0) ||
           (pcVar6 = strstr((char *)lpData,"RENDITION"), pcVar6 != (char *)0x0)) ||
          (pcVar6 = strstr((char *)lpData,"STEALTH II S220"), pcVar6 != (char *)0x0)) ||
         (pcVar6 = strstr((char *)lpData,"VIPER V330"), pcVar6 != (char *)0x0)) {
LAB_00504e3e:
        useHalfTexel = 1;
        if (local_3a90 == (HKEY)0x0) {
          useHalfTexel = 1;
          return;
        }
        RegCloseKey(local_3a90);
        return;
      }
      pBVar1 = aBStack_1684 + (int)local_3a8c;
      pcVar6 = strstr((char *)pBVar1,"NVIDIA");
      if ((pcVar6 != (char *)0x0) ||
         (pcVar6 = strstr((char *)pBVar1,"RENDITION"), pcVar6 != (char *)0x0)) goto LAB_00504e3e;
    }
    if (local_3a90 != (HKEY)0x0) {
      RegCloseKey(local_3a90);
    }
    local_3a8c = (BYTE *)((int)local_3a8c + 0x100);
    if (0xfff < (int)local_3a8c) {
      return;
    }
  } while( true );
}
