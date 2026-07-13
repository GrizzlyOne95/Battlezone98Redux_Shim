/*
 * Entry: 0051506f
 * Name: PartId_Id
 * Namespace: Global
 * Signature: int PartId_Id(tagPARTID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PartId_Id(tagPARTID *param_1)

{
  PartId_Valid(param_1);
  return param_1->partid;
}
