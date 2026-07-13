/*
 * Entry: 0051c8da
 * Name: Submit_AnimatedSky
 * Namespace: Global
 * Signature: void Submit_AnimatedSky(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_AnimatedSky(CAMERA *param_1)

{
  TEXTURE **ppTVar1;
  int iVar2;
  ulong uVar3;
  ulong uVar4;
  uint uVar5;
  DWORD DVar6;
  int iVar7;
  ulong *puVar8;
  CAMERA *unaff_ESI;
  CAMERA *unaff_EDI;
  int iVar9;
  int local_8;
  int local_4;
  
  if ((SkySet.bitmaps[0] != (TEXTURE **)0x0) && (local_4 = 0, 0 < SkySet.anims)) {
    puVar8 = &SkyActiveList[0].last;
    do {
      if (*puVar8 == 0) {
        local_8 = 0;
        iVar9 = SkySet.lastType;
        do {
          if (7 < local_8) break;
          if (iVar9 < 7) {
            iVar9 = iVar9 + 1;
          }
          else {
            iVar9 = 0;
          }
          if ((SkySet.name + iVar9 != (char (*) [16])0x0) && (SkySet.name[iVar9][0] != '\0')) {
            uVar5 = rand();
            ppTVar1 = SkySet.bitmaps[iVar9];
            SkySet.lastType = iVar9;
            puVar8[-8] = 0;
            uVar4 = SkySet.maxDelay;
            ((tagActiveSkyAnim *)(puVar8 + -0xb))->bitmaps = ppTVar1;
            puVar8[-10] = SkySet.frames[iVar9];
            uVar3 = SkySet.minDelay;
            iVar7 = uVar4 - SkySet.minDelay;
            puVar8[-2] = SkySet.animRate[iVar9];
            puVar8[-3] = SkySet.animSize[iVar9];
            iVar2 = SkySet.animDiam;
            puVar8[-1] = (iVar7 * (uVar5 & 0xffff) >> 0xf) + uVar3;
            puVar8[-9] = 1;
            puVar8[-4] = iVar2;
            GenerateSkyPos((tagActiveSkyAnim *)unaff_EDI,unaff_ESI);
            DVar6 = timeGetTime();
            *puVar8 = DVar6;
          }
          local_8 = local_8 + 1;
        } while (*puVar8 == 0);
      }
      if (*puVar8 != 0) {
        DVar6 = timeGetTime();
        if (*puVar8 + puVar8[-1] < DVar6) {
          DVar6 = timeGetTime();
          puVar8[-8] = puVar8[-8] + 1;
          *puVar8 = DVar6;
          if ((int)puVar8[-10] <= (int)puVar8[-8]) {
            puVar8[-9] = puVar8[-9] + -1;
            puVar8[-8] = 0;
            if ((int)puVar8[-9] < 1) {
              *puVar8 = 0;
            }
          }
          puVar8[-1] = puVar8[-2];
        }
        if ((*puVar8 != 0) && (puVar8[-8] != 0)) {
          GenerateSkyPoly((tagActiveSkyAnim *)param_1,unaff_EDI);
        }
      }
      local_4 = local_4 + 1;
      puVar8 = puVar8 + 0x30;
    } while (local_4 < SkySet.anims);
  }
  return;
}
