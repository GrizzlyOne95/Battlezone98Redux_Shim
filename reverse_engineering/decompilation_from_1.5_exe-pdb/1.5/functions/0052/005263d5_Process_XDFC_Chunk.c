/*
 * Entry: 005263d5
 * Name: Process_XDFC_Chunk
 * Namespace: Global
 * Signature: long Process_XDFC_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_XDFC_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  int iVar1;
  ChunkType *pCVar2;
  IDType *pIVar3;
  
  pCVar2 = param_1 + 1;
  pIVar3 = (IDType *)((int)param_2 + 0x14);
  for (iVar1 = 10; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pIVar3 = pCVar2->ckID;
    pCVar2 = (ChunkType *)&pCVar2->ckSize;
    pIVar3 = pIVar3 + 1;
  }
  return 1;
}
