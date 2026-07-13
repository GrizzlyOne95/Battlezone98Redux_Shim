/*
 * Entry: 00523f58
 * Name: Init_Zone_Manager
 * Namespace: Global
 * Signature: long Init_Zone_Manager(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Init_Zone_Manager(char *param_1)

{
  long lVar1;
  int iVar2;
  uint extraout_EAX;
  uint uVar3;
  uint uVar4;
  ushort *puVar5;
  size_t sVar6;
  uint *puVar7;
  
  iVar2 = OpenMemoryMapZoneFile();
  lVar1 = nZones;
  if (iVar2 == 0) {
    if (ZoneFileMap.Buffer == (char *)0x0) {
      sVar6 = nZones * 0x8000;
      GetINIInt("Size","Height",0,missionName);
      _ftol2();
      if (TerrainEdit == 0) {
        DEBUG_systemWarning("Terrain height file \"%s.hgt\" not found");
      }
      else {
        TraceError("Terrain height file \"%s.hgt\" not found\nFilling terrain with default height\n"
                  );
      }
      ZoneFileMap.Size = sVar6;
      ZoneFileMap.Buffer = malloc(sVar6);
      if (ZoneFileMap.Buffer < (uint *)((int)ZoneFileMap.Buffer + lVar1 * 0x2000 * 4)) {
        uVar3 = ((uint)((int)ZoneFileMap.Buffer + lVar1 * 0x2000 * 4 +
                       (-1 - (int)ZoneFileMap.Buffer)) >> 1) + 1;
        puVar7 = (uint *)ZoneFileMap.Buffer;
        for (uVar4 = uVar3 >> 1; uVar4 != 0; uVar4 = uVar4 - 1) {
          *puVar7 = extraout_EAX & 0xffff | (extraout_EAX & 0xffff) << 0x10;
          puVar7 = puVar7 + 1;
        }
        for (uVar3 = (uint)((uVar3 & 1) != 0); uVar3 != 0; uVar3 = uVar3 - 1) {
          *(short *)puVar7 = (short)extraout_EAX;
          puVar7 = (uint *)((int)puVar7 + 2);
        }
      }
    }
    if (MZoneFileMap.Buffer == (char *)0x0) {
      sVar6 = nZones << 0xd;
      if (TerrainEdit == 0) {
        DEBUG_systemWarning("Terrain material file \"%s.mat\" not found");
      }
      else {
        TraceError(
                  "Terrain material file \"%s.mat\" not found\nFilling terrain with default material\n"
                  );
      }
      MZoneFileMap.Size = sVar6;
      MZoneFileMap.Buffer = malloc(sVar6);
      memset(MZoneFileMap.Buffer,0,sVar6);
    }
  }
  lVar1 = nZones;
  iVar2 = 0;
  puVar5 = (ushort *)ZoneFileMap.Buffer;
  if (0 < nZones) {
    do {
      Zones[iVar2] = puVar5;
      iVar2 = iVar2 + 1;
      puVar5 = puVar5 + 0x4000;
    } while (iVar2 < lVar1);
  }
  return 1;
}
