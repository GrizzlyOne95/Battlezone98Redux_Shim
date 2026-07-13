/*
 * Entry: 005162d5
 * Name: Save_GetRandom
 * Namespace: Global
 * Signature: void Save_GetRandom(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Save_GetRandom(void)

{
  Save_Block_(1,&sync_offset,ST_ULONG,4);
  Save_Block_(1,&nonsync_offset,ST_ULONG,4);
  return;
}
