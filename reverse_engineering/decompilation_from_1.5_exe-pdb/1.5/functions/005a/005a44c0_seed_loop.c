/*
 * Entry: 005a44c0
 * Name: seed_loop
 * Namespace: Global
 * Signature: void seed_loop(vorbis_look_psy * param_1, float * * * param_2, float * param_3, float * param_4, float * param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
seed_loop(vorbis_look_psy *param_1,float ***param_2,float *param_3,float *param_4,float *param_5,
         float param_6)

{
  float fVar1;
  float **ppfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *unaff_EBX;
  int iVar8;
  float unaff_EDI;
  
  fVar1 = *(float *)(unaff_EBX[1] + 0x1f0);
  iVar3 = *unaff_EBX;
  iVar8 = 0;
  if (0 < iVar3) {
    do {
      ppfVar2 = param_2[iVar8];
      iVar4 = unaff_EBX[5];
      iVar7 = *(int *)(iVar4 + iVar8 * 4);
      iVar6 = iVar8;
      while ((iVar6 = iVar6 + 1, iVar6 < iVar3 && (*(int *)(iVar4 + 4 + iVar8 * 4) == iVar7))) {
        iVar5 = iVar8 + 1;
        iVar8 = iVar8 + 1;
        if ((float)ppfVar2 < (float)param_2[iVar5]) {
          ppfVar2 = param_2[iVar8];
        }
      }
      if (param_3[iVar8] < (float)ppfVar2 + 6.0) {
        iVar7 = iVar7 >> ((byte)unaff_EBX[8] & 0x1f);
        if (iVar7 < 0x11) {
          if (iVar7 < 0) {
            iVar7 = 0;
          }
        }
        else {
          iVar7 = 0x10;
        }
        seed_curve((float *)(&param_1->n)[iVar7],ppfVar2,
                   (float)(*(int *)(iVar4 + iVar8 * 4) - unaff_EBX[7]),unaff_EBX[10],unaff_EBX[9],
                   (int)(fVar1 - (float)param_5),unaff_EDI);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < iVar3);
  }
  return;
}
