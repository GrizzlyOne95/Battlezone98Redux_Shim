/*
 * Entry: 0051c2ec
 * Name: UnitId_Clear
 * Namespace: Global
 * Signature: void UnitId_Clear(tagUNITID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnitId_Clear(tagUNITID *param_1)

{
  Debug_Assert((int)param_1,0xf,".\\Schedule\\Unitid.c","uid");
  param_1->unitid = -1;
  param_1->unitp = (tagUNIT *)0x0;
  return;
}
