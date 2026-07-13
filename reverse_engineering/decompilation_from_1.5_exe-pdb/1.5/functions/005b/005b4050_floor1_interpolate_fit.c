/*
 * Entry: 005b4050
 * Name: floor1_interpolate_fit
 * Namespace: Global
 * Signature: int * floor1_interpolate_fit(vorbis_block * param_1, vorbis_look_floor1 * param_2, int * param_3, int * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int * __cdecl
floor1_interpolate_fit
          (vorbis_block *param_1,vorbis_look_floor1 *param_2,int *param_3,int *param_4,int param_5)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = param_2->posts;
  piVar1 = (int *)0x0;
  if (((param_3 != (int *)0x0) && (param_4 != (int *)0x0)) &&
     (piVar1 = _vorbis_block_alloc(param_1,iVar3 * 4), 0 < iVar3)) {
    iVar4 = (int)param_3 - (int)param_4;
    iVar5 = (int)piVar1 - (int)param_4;
    do {
      uVar2 = (int)((*param_4 & 0x7fffU) * param_5 + 0x8000 +
                   (*(uint *)(iVar4 + (int)param_4) & 0x7fff) * (0x10000 - param_5)) >> 0x10;
      *(uint *)(iVar5 + (int)param_4) = uVar2;
      if (((*(uint *)(iVar4 + (int)param_4) & 0x8000) != 0) && ((*param_4 & 0x8000U) != 0)) {
        *(uint *)(iVar5 + (int)param_4) = uVar2 | 0x8000;
      }
      param_4 = param_4 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return piVar1;
}
