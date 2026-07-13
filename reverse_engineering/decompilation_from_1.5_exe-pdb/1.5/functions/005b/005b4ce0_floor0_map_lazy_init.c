/*
 * Entry: 005b4ce0
 * Name: floor0_map_lazy_init
 * Namespace: Global
 * Signature: void floor0_map_lazy_init(vorbis_block * param_1, void * param_2, vorbis_look_floor0 * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl floor0_map_lazy_init(vorbis_block *param_1,void *param_2,vorbis_look_floor0 *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int in_EAX;
  void *pvVar4;
  int extraout_EAX;
  int iVar5;
  int iVar6;
  int iVar7;
  int *unaff_EDI;
  float10 fVar8;
  float10 fVar9;
  float10 fVar10;
  float10 fVar11;
  
  iVar3 = *(int *)(in_EAX + 0x1c);
  if (*(int *)(unaff_EDI[2] + iVar3 * 4) == 0) {
    iVar7 = *(int *)(*(int *)(*(int *)(*(int *)(in_EAX + 0x40) + 4) + 0x1c) + iVar3 * 4) / 2;
    iVar1 = (param_1->opb).endbyte;
    iVar2 = *unaff_EDI;
    fVar8 = (float10)__CIatan();
    fVar9 = (float10)__CIatan();
    pvVar4 = malloc(iVar7 * 4 + 4);
    *(void **)(unaff_EDI[2] + iVar3 * 4) = pvVar4;
    iVar6 = 0;
    if (0 < iVar7) {
      do {
        iVar5 = (param_1->opb).endbyte;
        fVar10 = (float10)__CIatan();
        fVar11 = (float10)__CIatan();
        floor((double)(((float10)((float)iVar6 * (((float)iVar5 * 0.5) / (float)iVar7)) *
                        (float10)9.999999747378752e-05 +
                       fVar11 * (float10)13.100000381469727 +
                       (float10)(double)(fVar10 * (float10)2.240000009536743)) *
                      (float10)(float)((float10)iVar2 /
                                      ((float10)((double)iVar1 * 0.5) *
                                       (float10)9.999999747378752e-05 +
                                      fVar9 * (float10)13.100000381469727 +
                                      (float10)(double)(fVar8 * (float10)2.240000009536743)))));
        _ftol2_sse();
        iVar5 = extraout_EAX;
        if (*unaff_EDI <= extraout_EAX) {
          iVar5 = *unaff_EDI + -1;
        }
        *(int *)(*(int *)(unaff_EDI[2] + iVar3 * 4) + iVar6 * 4) = iVar5;
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar7);
    }
    *(undefined4 *)(*(int *)(unaff_EDI[2] + iVar3 * 4) + iVar6 * 4) = 0xffffffff;
    unaff_EDI[iVar3 + 3] = iVar7;
  }
  return;
}
