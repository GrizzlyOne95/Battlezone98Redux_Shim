/*
 * Entry: 00524087
 * Name: Process_ZONE_Chunk
 * Namespace: Global
 * Signature: long Process_ZONE_Chunk(ChunkType * param_1, void * param_2, void * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl Process_ZONE_Chunk(ChunkType *param_1,void *param_2,void *param_3)

{
  long lVar1;
  int iVar2;
  ushort *puVar3;
  
  iVar2 = OpenMemoryMapZoneFile();
  lVar1 = nZones;
  if (iVar2 != 0) {
    iVar2 = 0;
    puVar3 = (ushort *)ZoneFileMap.Buffer;
    if (0 < nZones) {
      do {
        Zones[iVar2] = puVar3;
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 0x4000;
      } while (iVar2 < lVar1);
    }
    return 1;
  }
  DEBUG_systemError("Zone loader error");
  return 0;
}
