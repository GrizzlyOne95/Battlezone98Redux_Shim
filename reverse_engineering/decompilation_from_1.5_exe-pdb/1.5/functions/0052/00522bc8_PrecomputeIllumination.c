/*
 * Entry: 00522bc8
 * Name: PrecomputeIllumination
 * Namespace: Global
 * Signature: void PrecomputeIllumination(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl PrecomputeIllumination(void)

{
  undefined4 *puVar1;
  int iVar2;
  char *pcVar3;
  void *pvVar4;
  int iVar5;
  size_t sVar6;
  uint uVar7;
  long unaff_ESI;
  byte *pbVar8;
  long unaff_EDI;
  undefined4 *puVar9;
  float fVar10;
  size_t local_130;
  int local_12c;
  int local_128;
  uint local_124;
  int local_120;
  int local_11c;
  int local_118;
  size_t local_114;
  undefined1 local_110 [4];
  char local_10c [4];
  undefined1 auStack_108 [88];
  undefined1 local_b0 [168];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_b0;
  local_110 = (undefined1  [4])0x0;
  local_120 = 0;
  iVar5 = 1;
  memset(NormalsZoneTable,0,0x4000);
  iVar2 = 0;
  do {
    if (Terrain.Zone_Page_Table[iVar2] != &Empty_Zone) {
      NormalsZoneTable[iVar2] = (uchar)iVar5;
      iVar5 = iVar5 + 1;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x4000);
  sVar6 = iVar5 << 0xe;
  local_114 = sVar6;
  Normals = malloc(sVar6);
  if (Normals == (uchar *)0x0) {
    DEBUG_systemError("Memory allocation failed");
  }
  memset(Normals,0,sVar6);
  sprintf(local_10c,"%s",missionName);
  pcVar3 = strrchr(local_10c,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  puVar1 = (undefined4 *)(local_110 + 3);
  do {
    puVar9 = puVar1;
    puVar1 = (undefined4 *)((int)puVar9 + 1);
  } while (*(char *)((int)puVar9 + 1) != '\0');
  *(undefined4 *)((int)puVar9 + 1) = 0x54474c2e;
  *(undefined1 *)((int)puVar9 + 5) = 0;
  pvVar4 = zixReadFile(local_10c,(int *)&local_130);
  if (pvVar4 != (void *)0x0) {
    if (local_130 == local_114) {
      memcpy(Normals,pvVar4,local_130);
      local_120 = 1;
    }
    zixFree(pvVar4);
    if (local_120 != 0) goto LAB_00522d46;
  }
  sprintf(local_10c,"Addon\\%s",missionName);
  pcVar3 = strrchr(local_10c,0x2e);
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  puVar1 = (undefined4 *)(local_110 + 3);
  do {
    puVar9 = puVar1;
    puVar1 = (undefined4 *)((int)puVar9 + 1);
  } while (*(char *)((int)puVar9 + 1) != '\0');
  *(undefined4 *)((int)puVar9 + 1) = 0x54474c2e;
  *(undefined1 *)((int)puVar9 + 5) = 0;
  local_110 = (undefined1  [4])fopen(local_10c,"r+bc");
  if ((local_110 == (undefined1  [4])0x0) &&
     (local_110 = (undefined1  [4])fopen(local_10c,"w+bc"), local_110 == (undefined1  [4])0x0)) {
    DEBUG_systemError("Failed to open/create illumination file %s");
  }
LAB_00522d46:
  TerMaxY = 0.0;
  local_124 = 0;
  TerMinY = 4096.0;
  do {
    if (Terrain.Zone_Page_Table[local_124] != &Empty_Zone) {
      uVar7 = local_124 & 0x8000007f;
      if ((int)uVar7 < 0) {
        uVar7 = (uVar7 - 1 | 0xffffff80) + 1;
      }
      iVar2 = (((int)(local_124 + ((int)local_124 >> 0x1f & 0x7fU)) >> 7) + -0x18) * 0x80;
      local_11c = 0;
      local_12c = iVar2;
      do {
        iVar5 = local_11c + iVar2;
        local_128 = 0x80;
        local_118 = (uVar7 - 0x18) * 0x80;
        do {
          fVar10 = GetTerrainHeight(local_118,iVar5);
          if (TerMaxY < fVar10) {
            TerMaxY = fVar10;
          }
          if (fVar10 < TerMinY) {
            TerMinY = fVar10;
          }
          if (local_120 == 0) {
            ComputeNormal(unaff_EDI,unaff_ESI);
            iVar2 = local_12c;
          }
          local_118 = local_118 + 1;
          local_128 = local_128 + -1;
        } while (local_128 != 0);
        local_11c = local_11c + 1;
        local_128 = 0;
      } while (local_11c < 0x80);
    }
    pbVar8 = Normals;
    local_124 = local_124 + 1;
  } while ((int)local_124 < 0x4000);
  TerMaxY = TerMaxY * 10.0;
  TerMinY = TerMinY * 10.0;
  if (local_120 == 0) {
    BuildShadows();
    sVar6 = local_114;
    if (0 < (int)local_114) {
      do {
        if ((int)(uint)*pbVar8 < inShadow) {
          *pbVar8 = (byte)inShadow;
        }
        pbVar8 = pbVar8 + 1;
        sVar6 = sVar6 - 1;
      } while (sVar6 != 0);
    }
    if (local_110 == (undefined1  [4])0x0) {
      return;
    }
    fwrite(Normals,1,local_114,(FILE *)local_110);
  }
  if (local_110 != (undefined1  [4])0x0) {
    fclose((FILE *)local_110);
  }
  return;
}
