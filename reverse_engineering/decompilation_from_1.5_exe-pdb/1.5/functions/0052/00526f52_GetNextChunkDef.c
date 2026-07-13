/*
 * Entry: 00526f52
 * Name: GetNextChunkDef
 * Namespace: Global
 * Signature: int GetNextChunkDef(CHUNKDEF * * param_1, long * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetNextChunkDef(CHUNKDEF **param_1,long *param_2)

{
  *param_2 = *param_2 + -1;
  if (*param_2 == 0) {
    return 0;
  }
  *param_1 = *param_1 + 1;
  return 1;
}
