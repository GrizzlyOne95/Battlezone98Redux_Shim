/*
 * Entry: 0051c36d
 * Name: UnitId_Ptr
 * Namespace: Global
 * Signature: tagUNIT * UnitId_Ptr(tagUNITID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagUNIT * __cdecl UnitId_Ptr(tagUNITID *param_1)

{
  UnitId_Valid(param_1);
  return param_1->unitp;
}
