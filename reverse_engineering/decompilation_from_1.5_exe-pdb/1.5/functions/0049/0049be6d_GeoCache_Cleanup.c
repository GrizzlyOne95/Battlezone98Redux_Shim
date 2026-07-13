/*
 * Entry: 0049be6d
 * Name: GeoCache_Cleanup
 * Namespace: Global
 * Signature: void GeoCache_Cleanup(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GeoCache_Cleanup(void)

{
  undefined4 *puVar1;
  void *pvVar2;
  uint uVar3;
  
  uVar3 = 0;
  do {
    puVar1 = (undefined4 *)((int)&gcache[0].data + uVar3);
    pvVar2 = (void *)*puVar1;
    if (pvVar2 != (void *)0x0) {
      operator_delete__(pvVar2);
      *puVar1 = 0;
    }
    uVar3 = uVar3 + 0x18;
  } while (uVar3 < 0x6000);
  return;
}
