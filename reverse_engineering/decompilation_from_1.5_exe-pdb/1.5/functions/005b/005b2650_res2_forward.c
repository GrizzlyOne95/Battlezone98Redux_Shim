/*
 * Entry: 005b2650
 * Name: res2_forward
 * Namespace: Global
 * Signature: int res2_forward(oggpack_buffer * param_1, vorbis_block * param_2, void * param_3, int * * param_4, int * param_5, int param_6, long * * param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
res2_forward(oggpack_buffer *param_1,vorbis_block *param_2,void *param_3,int **param_4,int *param_5,
            int param_6,long **param_7,int param_8)

{
  int iVar1;
  vorbis_block *pvVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int local_10;
  int *local_4;
  
  pvVar2 = param_2;
  iVar7 = param_2->pcmend / 2;
  param_2 = (vorbis_block *)0x0;
  local_4 = _vorbis_block_alloc(pvVar2,iVar7 * param_6 * 4);
  if (0 < param_6) {
    iVar6 = (int)param_4 - (int)param_5;
    iVar4 = (int)local_4 - (int)param_5;
    local_10 = param_6;
    do {
      iVar1 = *(int *)(iVar6 + (int)param_5);
      if (*param_5 != 0) {
        param_2 = (vorbis_block *)((int)&param_2->pcm + 1);
      }
      iVar3 = 0;
      if (0 < iVar7) {
        puVar5 = (undefined4 *)(iVar4 + (int)param_5);
        do {
          *puVar5 = *(undefined4 *)(iVar1 + iVar3 * 4);
          iVar3 = iVar3 + 1;
          puVar5 = puVar5 + param_6;
        } while (iVar3 < iVar7);
      }
      param_5 = param_5 + 1;
      local_10 = local_10 + -1;
    } while (local_10 != 0);
    if (param_2 != (vorbis_block *)0x0) {
      iVar7 = _01forward(param_1,param_3,&local_4,1,param_7,_encodepart);
      return iVar7;
    }
  }
  return 0;
}
