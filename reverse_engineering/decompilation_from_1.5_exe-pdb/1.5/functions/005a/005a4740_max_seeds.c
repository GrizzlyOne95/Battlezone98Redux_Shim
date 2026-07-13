/*
 * Entry: 005a4740
 * Name: max_seeds
 * Namespace: Global
 * Signature: void max_seeds(vorbis_look_psy * param_1, float * param_2, float * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl max_seeds(vorbis_look_psy *param_1,float *param_2,float *param_3)

{
  vorbis_info_psy *pvVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int *unaff_EDI;
  
  iVar5 = unaff_EDI[9];
  iVar6 = 0;
  seed_chase((float *)param_1,iVar5,unaff_EDI[10]);
  iVar5 = (*(int *)unaff_EDI[5] - (iVar5 >> 1)) - unaff_EDI[7];
  if (1 < *unaff_EDI) {
    do {
      pvVar1 = (vorbis_info_psy *)(&param_1->n)[iVar5];
      iVar4 = iVar5;
      iVar3 = iVar5;
      if (*(float *)(unaff_EDI[1] + 0x20) < (float)pvVar1) {
        pvVar1 = *(vorbis_info_psy **)(unaff_EDI[1] + 0x20);
      }
      while (iVar5 = iVar4, iVar3 = iVar3 + 1,
            iVar3 <= (*(int *)(unaff_EDI[5] + 4 + iVar6 * 4) + *(int *)(unaff_EDI[5] + iVar6 * 4) >>
                     1) - unaff_EDI[7]) {
        iVar4 = iVar5 + 1;
        if (((-9999.0 < (float)(&param_1->vi)[iVar5]) &&
            ((float)(&param_1->vi)[iVar5] < (float)pvVar1)) || ((float)pvVar1 == -9999.0)) {
          pvVar1 = (&param_1->vi)[iVar5];
        }
      }
      iVar3 = unaff_EDI[7];
      if (iVar6 < *unaff_EDI) {
        do {
          if (iVar3 + iVar5 < *(int *)(unaff_EDI[5] + iVar6 * 4)) break;
          if (param_2[iVar6] < (float)pvVar1) {
            param_2[iVar6] = (float)pvVar1;
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < *unaff_EDI);
      }
    } while (iVar6 + 1 < *unaff_EDI);
  }
  fVar2 = *(float *)((int)param_1 + unaff_EDI[10] * 4 + -4);
  if (iVar6 < *unaff_EDI) {
    do {
      if (param_2[iVar6] < fVar2) {
        param_2[iVar6] = fVar2;
      }
      iVar6 = iVar6 + 1;
    } while (iVar6 < *unaff_EDI);
  }
  return;
}
