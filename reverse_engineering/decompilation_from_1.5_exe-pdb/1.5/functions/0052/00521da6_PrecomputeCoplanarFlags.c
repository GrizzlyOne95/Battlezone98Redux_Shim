/*
 * Entry: 00521da6
 * Name: PrecomputeCoplanarFlags
 * Namespace: Global
 * Signature: void PrecomputeCoplanarFlags(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PrecomputeCoplanarFlags(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint local_4;
  
  local_4 = 0;
  do {
    if (Terrain.Zone_Page_Table[local_4] != &Empty_Zone) {
      uVar3 = local_4 & 0x8000007f;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xffffff80) + 1;
      }
      iVar2 = 0;
      do {
        iVar1 = 0;
        do {
          ComputeCoplanarFlags
                    (iVar1 + (uVar3 - 0x18) * 0x80,
                     (((int)(local_4 + ((int)local_4 >> 0x1f & 0x7fU)) >> 7) + -0x18) * 0x80 + iVar2
                    );
          iVar1 = iVar1 + 1;
        } while (iVar1 < 0x80);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x80);
    }
    local_4 = local_4 + 1;
  } while ((int)local_4 < 0x4000);
  return;
}
