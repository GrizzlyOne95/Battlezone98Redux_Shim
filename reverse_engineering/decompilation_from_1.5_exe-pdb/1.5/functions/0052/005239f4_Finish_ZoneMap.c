/*
 * Entry: 005239f4
 * Name: Finish_ZoneMap
 * Namespace: Global
 * Signature: long Finish_ZoneMap(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Finish_ZoneMap(ChunkType *param_1,void *param_2,void *param_3)

{
  int iVar1;
  
  iVar1 = Terrain_Create(1,(uint)(UserProfilePtr->graphicDetail).terrain,5.0);
  return iVar1;
}
