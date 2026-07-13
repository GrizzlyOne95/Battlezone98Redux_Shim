/*
 * Entry: 0051c37d
 * Name: UnitId_Id
 * Namespace: Global
 * Signature: int UnitId_Id(tagUNITID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl UnitId_Id(tagUNITID *param_1)

{
  UnitId_Valid(param_1);
  return param_1->unitid;
}
