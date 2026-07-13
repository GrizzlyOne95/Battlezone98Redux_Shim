/*
 * Entry: 0051505f
 * Name: PartId_Ptr
 * Namespace: Global
 * Signature: tagPART * PartId_Ptr(tagPARTID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagPART * __cdecl PartId_Ptr(tagPARTID *param_1)

{
  PartId_Valid(param_1);
  return param_1->partp;
}
