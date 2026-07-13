/*
 * Entry: 0051c30f
 * Name: UnitId_Setup
 * Namespace: Global
 * Signature: void UnitId_Setup(tagUNITID * param_1, tagUNIT * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl UnitId_Setup(tagUNITID *param_1,tagUNIT *param_2)

{
  Debug_Assert((int)param_1,0x17,".\\Schedule\\Unitid.c","uid");
  param_1->unitid = param_2->id;
  param_1->unitp = param_2;
  return;
}
