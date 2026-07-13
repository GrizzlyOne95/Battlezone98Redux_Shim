/*
 * Entry: 005b4fe0
 * Name: floor0_inverse2
 * Namespace: Global
 * Signature: int floor0_inverse2(vorbis_block * param_1, void * param_2, void * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl floor0_inverse2(vorbis_block *param_1,void *param_2,void *param_3,float *param_4)

{
  vorbis_block *pvVar1;
  vorbis_look_floor0 *unaff_ESI;
  void *unaff_EDI;
  
  pvVar1 = *(vorbis_block **)((int)param_2 + 0x14);
  floor0_map_lazy_init(pvVar1,unaff_EDI,unaff_ESI);
  if (param_3 != (void *)0x0) {
    vorbis_lsp_to_curve(param_4,*(int **)(*(int *)((int)param_2 + 8) + param_1->W * 4),
                        *(int *)((int)param_2 + param_1->W * 4 + 0xc),*(int *)param_2,param_3,
                        *(int *)((int)param_2 + 4),
                        *(float *)((int)param_3 + *(int *)((int)param_2 + 4) * 4),
                        (float)(int)(pvVar1->opb).ptr);
    return 1;
  }
  memset(param_4,0,*(int *)((int)param_2 + param_1->W * 4 + 0xc) * 4);
  return 0;
}
