/*
 * Entry: 0051d948
 * Name: Submit_AnimatedScrounge
 * Namespace: Global
 * Signature: void Submit_AnimatedScrounge(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Submit_AnimatedScrounge(CAMERA *param_1)

{
  TEXTURE **ppTVar1;
  int iVar2;
  uint uVar3;
  DWORD DVar4;
  int iVar5;
  CAMERA *unaff_ESI;
  int *piVar6;
  int local_4;
  
  if ((AnimSet[0].bitmaps[0] != (TEXTURE **)0x0) && (local_4 = 0, 0 < animCount)) {
    piVar6 = &AnimActiveList[0].loops;
    do {
      if (piVar6[6] == 0) {
        iVar2 = GenerateAnimPos((tagActiveAnim *)(piVar6 + -3),unaff_ESI);
        if (-1 < iVar2) {
          uVar3 = rand();
          iVar5 = (int)(AnimSet[iVar2].anims * (uVar3 & 0xffff)) >> 0xf;
          ppTVar1 = AnimSet[iVar2].bitmaps[iVar5];
          iVar2 = AnimSet[iVar2].frames[iVar5];
          piVar6[-1] = 0;
          ((tagActiveAnim *)(piVar6 + -3))->bitmaps = ppTVar1;
          iVar5 = animRate;
          piVar6[-2] = iVar2;
          *piVar6 = 1;
          piVar6[5] = (int)(iVar2 * iVar5 * (uVar3 & 0xffff)) >> 0xf;
          piVar6[4] = iVar5;
          DVar4 = timeGetTime();
          piVar6[6] = DVar4;
        }
        if (piVar6[6] != 0) goto LAB_0051d9f0;
      }
      else {
LAB_0051d9f0:
        DVar4 = timeGetTime();
        if ((uint)(piVar6[6] + piVar6[5]) < DVar4) {
          DVar4 = timeGetTime();
          piVar6[-1] = piVar6[-1] + 1;
          piVar6[6] = DVar4;
          if (piVar6[-2] <= piVar6[-1]) {
            *piVar6 = *piVar6 + -1;
            piVar6[-1] = 0;
            if (*piVar6 < 1) {
              piVar6[6] = 0;
            }
          }
          piVar6[5] = piVar6[4];
        }
        if ((piVar6[6] != 0) && (piVar6[-1] != 0)) {
          GenerateAnimPoly((tagActiveAnim *)param_1,(CAMERA *)((float)animSize * 0.01),
                           (float)animSize * 0.01,(float)unaff_ESI);
        }
      }
      local_4 = local_4 + 1;
      piVar6 = piVar6 + 0x2e;
    } while (local_4 < animCount);
  }
  return;
}
