/*
 * Entry: 00526bc6
 * Name: Process_VDFC_Chunk
 * Namespace: Global
 * Signature: long Process_VDFC_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_VDFC_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  int iVar1;
  ChunkType *pCVar2;
  IDType *pIVar3;
  
  if (*(int *)(*(int *)param_2 + 0xb0) != 0) {
    *(long *)(*(int *)(*(int *)param_2 + 0xb0) + 4) = param_1[6].ckSize;
  }
  pCVar2 = param_1 + 4;
  pIVar3 = (IDType *)((int)param_2 + 0x3c);
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pIVar3 = pCVar2->ckID;
    pCVar2 = (ChunkType *)&pCVar2->ckSize;
    pIVar3 = pIVar3 + 1;
  }
  *(undefined4 *)((int)param_2 + 0x50) = 1;
  return 1;
}
