/*
 * Entry: 0051ed0d
 * Name: Terrain_Init_PathPlan
 * Namespace: Global
 * Signature: void Terrain_Init_PathPlan(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Terrain_Init_PathPlan(void)

{
  int iVar1;
  int extraout_EAX;
  int iVar2;
  PAGE **ppPVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_c;
  PAGE **local_8;
  
  iVar2 = 0;
  iVar5 = 0x50;
  local_c = 0;
  iVar4 = 0;
  local_8 = Terrain.Zone_Page_Table + 0xc18;
  iVar6 = iVar5;
  do {
    iVar1 = 0;
    ppPVar3 = local_8;
    do {
      if (*ppPVar3 != &Empty_Zone) {
        if (iVar1 < iVar6) {
          iVar6 = iVar1;
        }
        if (local_c < iVar1) {
          local_c = iVar1;
        }
        if (iVar2 < iVar5) {
          iVar5 = iVar2;
        }
        if (iVar4 < iVar2) {
          iVar4 = iVar2;
        }
      }
      iVar1 = iVar1 + 1;
      ppPVar3 = ppPVar3 + 1;
    } while (iVar1 < 0x50);
    local_8 = local_8 + 0x80;
    iVar2 = iVar2 + 1;
  } while ((int)local_8 < 0xcd09c4);
  _ftol2_sse();
  grid_rect.left = iVar6 * 0x80 * extraout_EAX;
  grid_rect.top = iVar5 * 0x80 * extraout_EAX;
  grid_rect.bottom = (iVar4 + 1) * extraout_EAX * 0x80;
  grid_rect.right = (local_c + 1) * extraout_EAX * 0x80;
  return;
}
