/*
 * Entry: 00526c60
 * Name: Process_COLP_Chunk
 * Namespace: Global
 * Signature: long Process_COLP_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_COLP_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  int iVar1;
  ChunkType *pCVar2;
  IDType *pIVar3;
  
  pCVar2 = param_1 + 1;
  pIVar3 = (IDType *)((int)param_2 + 0xc);
  for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pIVar3 = pCVar2->ckID;
    pCVar2 = (ChunkType *)&pCVar2->ckSize;
    pIVar3 = pIVar3 + 1;
  }
  *(undefined4 *)((int)param_2 + 8) = 1;
  return 1;
}
