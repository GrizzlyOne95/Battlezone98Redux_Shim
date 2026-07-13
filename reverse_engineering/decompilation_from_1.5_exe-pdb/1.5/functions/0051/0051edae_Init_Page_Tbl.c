/*
 * Entry: 0051edae
 * Name: Init_Page_Tbl
 * Namespace: Global
 * Signature: void Init_Page_Tbl(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_Page_Tbl(void)

{
  uint extraout_EAX;
  PAGE *pPVar1;
  ushort *puVar2;
  int iVar3;
  int iVar4;
  PAGE **ppPVar5;
  ushort **ppuVar6;
  int iVar7;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  byte *local_8;
  
  _ftol2();
  ppPVar5 = Terrain.Zone_Page_Table;
  for (iVar3 = 0x4000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *ppPVar5 = &Empty_Zone;
    ppPVar5 = ppPVar5 + 1;
  }
  iVar3 = 0x2000;
  puVar2 = Empty_Zone.Height;
  for (; iVar3 != 0; iVar3 = iVar3 + -1) {
    *(uint *)puVar2 = extraout_EAX & 0xffff | (extraout_EAX & 0xffff) << 0x10;
    puVar2 = puVar2 + 2;
  }
  iVar3 = 0;
  local_c = 0x50;
  local_14 = 0x50;
  local_18 = 0;
  local_1c = 0;
  local_8 = (byte *)GetZoneMap();
  local_10 = 0;
  do {
    iVar4 = 0;
    do {
      if (*local_8 != 0xff) {
        pPVar1 = (PAGE *)GetZone((uint)*local_8);
        Terrain.Zone_Page_Table[iVar3 + iVar4 + 0xc18] = pPVar1;
        if (local_10 < local_14) {
          local_14 = local_10;
        }
        if (iVar4 < local_c) {
          local_c = iVar4;
        }
        if (local_18 < iVar4) {
          local_18 = iVar4;
        }
        if (local_1c < local_10) {
          local_1c = local_10;
        }
      }
      local_8 = local_8 + 1;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x50);
    local_10 = local_10 + 1;
    iVar3 = iVar3 + 0x80;
  } while (iVar3 < 0x2800);
  memset(Empty_MZone,0,0x8000);
  ppuVar6 = TexelsZoneTable;
  for (iVar3 = 0x4000; iVar3 != 0; iVar3 = iVar3 + -1) {
    *ppuVar6 = Empty_MZone;
    ppuVar6 = ppuVar6 + 1;
  }
  local_8 = (byte *)GetZoneMap();
  iVar3 = 0;
  iVar4 = -local_14;
  do {
    iVar7 = 0;
    do {
      if (*local_8 != -1) {
        puVar2 = GetMZone();
        TexelsZoneTable[iVar3 + iVar7 + 0xc18] =
             puVar2 + ((((local_18 - local_c) + 1) * iVar4 - local_c) + iVar7) * 0x1000;
      }
      local_8 = local_8 + 1;
      iVar7 = iVar7 + 1;
    } while (iVar7 < 0x50);
    iVar3 = iVar3 + 0x80;
    iVar4 = iVar4 + 1;
  } while (iVar3 < 0x2800);
  GridMinX = local_c << 7;
  GridMaxX = (local_18 + 1) * 0x80;
  TerMinX = (float)(local_c << 7) * 10.0;
  GridMinZ = local_14 << 7;
  GridMaxZ = (local_1c + 1) * 0x80;
  TerMaxX = (float)GridMaxX * 10.0;
  TerMinZ = (float)(local_14 << 7) * 10.0;
  TerMaxZ = (float)GridMaxZ * 10.0;
  return;
}
