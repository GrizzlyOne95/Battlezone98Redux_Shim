/*
 * Entry: 005134a9
 * Name: Mapgrid_Done
 * Namespace: Global
 * Signature: void Mapgrid_Done(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_Done(void)

{
  if (mapgrid != (tagMAPGRID **)0x0) {
    free(*mapgrid);
    free(mapgrid);
    mapgrid = (tagMAPGRID **)0x0;
  }
  return;
}
