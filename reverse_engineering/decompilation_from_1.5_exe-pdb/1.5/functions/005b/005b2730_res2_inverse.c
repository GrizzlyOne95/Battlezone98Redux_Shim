/*
 * Entry: 005b2730
 * Name: res2_inverse
 * Namespace: Global
 * Signature: int res2_inverse(vorbis_block * param_1, void * param_2, float * * param_3, int * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
res2_inverse(vorbis_block *param_1,void *param_2,float **param_3,int *param_4,int param_5)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  codebook *pcVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  long lVar9;
  int iVar10;
  int local_18;
  int local_14;
  int *local_10;
  
  iVar1 = **(int **)((int)param_2 + 0x10);
  piVar2 = *(int **)param_2;
  iVar3 = piVar2[2];
  iVar6 = param_1->pcmend * param_5 >> 1;
  if (piVar2[1] < iVar6) {
    iVar6 = piVar2[1];
  }
  if (0 < iVar6 - *piVar2) {
    iVar6 = (iVar6 - *piVar2) / iVar3;
    piVar7 = _vorbis_block_alloc(param_1,((iVar6 + -1 + iVar1) / iVar1) * 4);
    iVar8 = 0;
    if (0 < param_5) {
      do {
        if (param_4[iVar8] != 0) break;
        iVar8 = iVar8 + 1;
      } while (iVar8 < param_5);
    }
    if ((iVar8 != param_5) && (local_14 = 0, 0 < *(int *)((int)param_2 + 8))) {
      do {
        local_18 = 0;
        local_10 = piVar7;
        if (0 < iVar6) {
          do {
            if (local_14 == 0) {
              lVar9 = vorbis_book_decode(*(codebook **)((int)param_2 + 0x10),&param_1->opb);
              if (lVar9 == -1) {
                return 0;
              }
              if (piVar2[4] <= lVar9) {
                return 0;
              }
              iVar8 = *(int *)(*(int *)((int)param_2 + 0x1c) + lVar9 * 4);
              *local_10 = iVar8;
              if (iVar8 == 0) {
                return 0;
              }
            }
            iVar8 = 0;
            if (0 < iVar1) {
              iVar10 = local_18 * iVar3;
              do {
                if (iVar6 <= local_18) break;
                iVar4 = *(int *)(*local_10 + iVar8 * 4);
                if ((((piVar2[iVar4 + 6] & 1 << ((byte)local_14 & 0x1f)) != 0) &&
                    (pcVar5 = *(codebook **)
                               (*(int *)(*(int *)((int)param_2 + 0x14) + iVar4 * 4) + local_14 * 4),
                    pcVar5 != (codebook *)0x0)) &&
                   (lVar9 = vorbis_book_decodevv_add
                                      (pcVar5,param_3,*piVar2 + iVar10,param_5,&param_1->opb,iVar3),
                   lVar9 == -1)) {
                  return 0;
                }
                local_18 = local_18 + 1;
                iVar8 = iVar8 + 1;
                iVar10 = iVar10 + iVar3;
              } while (iVar8 < iVar1);
            }
            local_10 = local_10 + 1;
          } while (local_18 < iVar6);
        }
        local_14 = local_14 + 1;
      } while (local_14 < *(int *)((int)param_2 + 8));
    }
  }
  return 0;
}
