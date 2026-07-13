/*
 * Entry: 005b1f20
 * Name: _2class
 * Namespace: Global
 * Signature: long * * _2class(vorbis_block * param_1, void * param_2, int * * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long ** __cdecl _2class(vorbis_block *param_1,void *param_2,int **param_3,int param_4)

{
  float **ppfVar1;
  float *pfVar2;
  float *pfVar3;
  uint uVar4;
  vorbis_block *in_EAX;
  int iVar5;
  long **pplVar6;
  long *plVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  float **ppfVar11;
  uint uVar12;
  int iVar13;
  int local_20;
  int local_18;
  int local_10;
  
  ppfVar1 = param_1->pcm;
  pfVar2 = ppfVar1[2];
  iVar5 = ((int)ppfVar1[1] - (int)*ppfVar1) / (int)pfVar2;
  pfVar3 = ppfVar1[3];
  pplVar6 = _vorbis_block_alloc(in_EAX,4);
  plVar7 = _vorbis_block_alloc(in_EAX,iVar5 * 4);
  *pplVar6 = plVar7;
  memset(plVar7,0,iVar5 * 4);
  iVar8 = (int)*ppfVar1 / (int)param_3;
  local_10 = 0;
  if (0 < iVar5) {
    do {
      iVar13 = 0;
      local_20 = 0;
      local_18 = 0;
      iVar9 = 0;
      if (0 < (int)pfVar2) {
        do {
          uVar4 = *(uint *)(*(int *)param_2 + iVar8 * 4);
          uVar12 = (int)uVar4 >> 0x1f;
          iVar9 = (uVar4 ^ uVar12) - uVar12;
          if (local_20 < iVar9) {
            local_20 = iVar9;
          }
          iVar9 = 1;
          if (1 < (int)param_3) {
            do {
              uVar4 = *(uint *)(*(int *)((int)param_2 + iVar9 * 4) + iVar8 * 4);
              uVar12 = (int)uVar4 >> 0x1f;
              iVar10 = (uVar4 ^ uVar12) - uVar12;
              if (iVar13 < iVar10) {
                iVar13 = iVar10;
              }
              iVar9 = iVar9 + 1;
            } while (iVar9 < (int)param_3);
          }
          local_18 = local_18 + (int)param_3;
          iVar8 = iVar8 + 1;
          iVar9 = local_20;
        } while (local_18 < (int)pfVar2);
      }
      iVar10 = 0;
      if (0 < (int)pfVar3 + -1) {
        ppfVar11 = ppfVar1 + 0x286;
        do {
          if ((iVar9 <= (int)ppfVar11[-0x40]) && (iVar13 <= (int)*ppfVar11)) break;
          iVar10 = iVar10 + 1;
          ppfVar11 = ppfVar11 + 1;
        } while (iVar10 < (int)pfVar3 + -1);
      }
      (*pplVar6)[local_10] = iVar10;
      local_10 = local_10 + 1;
    } while (local_10 < iVar5);
  }
  param_1->mode = param_1->mode + 1;
  return pplVar6;
}
