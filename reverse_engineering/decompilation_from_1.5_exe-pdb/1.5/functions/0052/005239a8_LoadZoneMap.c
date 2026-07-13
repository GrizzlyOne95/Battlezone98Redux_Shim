/*
 * Entry: 005239a8
 * Name: LoadZoneMap
 * Namespace: Global
 * Signature: long LoadZoneMap(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl LoadZoneMap(ChunkType *param_1,void *param_2,void *param_3)

{
  ChunkType *pCVar1;
  
  memset(ZoneMap,0xffffffff,0x1900);
  memset(Zones,0,0x6400);
  pCVar1 = GenericChunkHandler(param_1,TerrainChunkDefs,4,(void *)0x0,param_2,1,param_3);
  return (uint)(pCVar1 != (ChunkType *)0x0);
}
