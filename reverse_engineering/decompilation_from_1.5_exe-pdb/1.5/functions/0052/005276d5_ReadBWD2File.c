/*
 * Entry: 005276d5
 * Name: ReadBWD2File
 * Namespace: Global
 * Signature: int ReadBWD2File(char * param_1, CHUNKDEF * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ReadBWD2File(char *param_1,CHUNKDEF *param_2,long param_3,void *param_4)

{
  int iVar1;
  ChunkType *pCVar2;
  long lVar3;
  ChunkType *pCVar4;
  void *pvVar5;
  
  if (param_1 == (char *)0x0) {
    return 0;
  }
  iVar1 = _strnicmp(param_1,"null",4);
  if (iVar1 == 0) {
    return 1;
  }
  pCVar2 = UseItem(param_1);
  pCVar4 = (ChunkType *)0x0;
  if (pCVar2 != (ChunkType *)0x0) {
    lVar3 = GetItemSize(param_1);
    pvVar5 = (void *)((int)&pCVar2->ckID + lVar3);
    pCVar2 = VerifyAndSkipBWD2Header(pCVar2,param_1,pvVar5);
    pCVar4 = (ChunkType *)0x0;
    if (pCVar2 != (ChunkType *)0x0) {
      pCVar4 = GenericChunkHandler(pCVar2,param_2,param_3,param_4,param_1,1,pvVar5);
    }
    UnlockItem(param_1);
  }
  return (uint)(pCVar4 != (ChunkType *)0x0);
}
