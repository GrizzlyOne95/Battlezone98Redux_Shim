/*
 * Entry: 0051c336
 * Name: UnitId_Valid
 * Namespace: Global
 * Signature: int UnitId_Valid(tagUNITID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UnitId_Valid(tagUNITID *param_1)

{
  Debug_Assert((int)param_1,0x1f,".\\Schedule\\Unitid.c","uid");
  if ((param_1->unitp != (tagUNIT *)0x0) && (param_1->unitp->id == param_1->unitid)) {
    return 1;
  }
  UnitId_Clear(param_1);
  return 0;
}
