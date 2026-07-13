/*
 * Entry: 0049b442
 * Name: GeoCache_Init
 * Namespace: Global
 * Signature: void GeoCache_Init(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GeoCache_Init(void)

{
  uint uVar1;
  
  gcacheCount = 0;
  uVar1 = 0;
  do {
    *(undefined4 *)((int)&gcache[0].data + uVar1) = 0;
    uVar1 = uVar1 + 0x18;
  } while (uVar1 < 0x6000);
  return;
}
