/*
 * Entry: 005b1d90
 * Name: _01class
 * Namespace: Global
 * Signature: long * * _01class(vorbis_block * param_1, void * param_2, int * * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long ** __cdecl _01class(vorbis_block *param_1,void *param_2,int **param_3,int param_4)

{
  float **ppfVar1;
  float *pfVar2;
  float *pfVar3;
  float *pfVar4;
  vorbis_block *in_EAX;
  int iVar5;
  long **pplVar6;
  long *plVar7;
  int iVar8;
  int extraout_EAX;
  uint *puVar9;
  long lVar10;
  uint uVar11;
  float **ppfVar12;
  long **pplVar13;
  int iVar14;
  float *pfVar15;
  int local_28;
  int **local_1c;
  int local_10;
  
  ppfVar1 = param_1->pcm;
  pfVar2 = ppfVar1[3];
  pfVar3 = ppfVar1[2];
  iVar5 = ((int)ppfVar1[1] - (int)*ppfVar1) / (int)pfVar3;
  pplVar6 = _vorbis_block_alloc(in_EAX,(int)param_3 * 4);
  iVar14 = 0;
  if (0 < (int)param_3) {
    do {
      plVar7 = _vorbis_block_alloc(in_EAX,iVar5 * 4);
      pplVar6[iVar14] = plVar7;
      memset(plVar7,0,iVar5 * 4);
      iVar14 = iVar14 + 1;
    } while (iVar14 < (int)param_3);
  }
  local_28 = 0;
  if (0 < iVar5) {
    local_10 = 0;
    do {
      pfVar4 = *ppfVar1;
      if (0 < (int)param_3) {
        local_1c = param_3;
        pplVar13 = pplVar6;
        do {
          iVar14 = 0;
          if (0 < (int)pfVar3) {
            puVar9 = (uint *)(*(int *)(((int)param_2 - (int)pplVar6) + (int)pplVar13) +
                             ((int)pfVar4 + local_10) * 4);
            pfVar15 = pfVar3;
            do {
              uVar11 = (int)*puVar9 >> 0x1f;
              iVar8 = (*puVar9 ^ uVar11) - uVar11;
              if (iVar14 < iVar8) {
                iVar14 = iVar8;
              }
              puVar9 = puVar9 + 1;
              pfVar15 = (float *)((int)pfVar15 + -1);
            } while (pfVar15 != (float *)0x0);
          }
          _ftol2_sse();
          lVar10 = 0;
          if (0 < (int)pfVar2 + -1) {
            ppfVar12 = ppfVar1 + 0x286;
            do {
              if ((iVar14 <= (int)ppfVar12[-0x40]) &&
                 (((int)*ppfVar12 < 0 || (extraout_EAX < (int)*ppfVar12)))) break;
              lVar10 = lVar10 + 1;
              ppfVar12 = ppfVar12 + 1;
            } while (lVar10 < (int)pfVar2 + -1);
          }
          plVar7 = *pplVar13;
          pplVar13 = pplVar13 + 1;
          local_1c = (int **)((int)local_1c + -1);
          plVar7[local_28] = lVar10;
        } while (local_1c != (int **)0x0);
      }
      local_10 = local_10 + (int)pfVar3;
      local_28 = local_28 + 1;
    } while (local_28 < iVar5);
  }
  param_1->mode = param_1->mode + 1;
  return pplVar6;
}
