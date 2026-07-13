/*
 * Entry: 0051f88d
 * Name: Terrain_Close
 * Namespace: Global
 * Signature: void Terrain_Close(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Terrain_Close(void)

{
  FreeZones();
  if ((Normals != (uchar *)0x0) && (hDefaultHeap != (void *)0x0)) {
    free(Normals);
  }
  return;
}
