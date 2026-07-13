/*
 * Entry: 00523a27
 * Name: GetMZone
 * Namespace: Global
 * Signature: ushort * GetMZone(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl GetMZone(void)

{
  return (ushort *)MZoneFileMap.Buffer;
}
