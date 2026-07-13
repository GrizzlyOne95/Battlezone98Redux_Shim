/*
 * Entry: 00525827
 * Name: Process_SDFC_Chunk
 * Namespace: Global
 * Signature: long Process_SDFC_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_SDFC_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  int iVar1;
  long *plVar2;
  long *plVar3;
  
  plVar2 = &param_1[3].ckSize;
  plVar3 = (long *)((int)param_2 + 0x3c);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *plVar3 = *plVar2;
    plVar2 = plVar2 + 1;
    plVar3 = plVar3 + 1;
  }
  *(undefined4 *)((int)param_2 + 0x50) = 1;
  return 1;
}
