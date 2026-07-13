/*
 * Entry: 00515028
 * Name: PartId_Valid
 * Namespace: Global
 * Signature: int PartId_Valid(tagPARTID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PartId_Valid(tagPARTID *param_1)

{
  Debug_Assert((int)param_1,0x1e,".\\Schedule\\Partid.c","pid");
  if ((param_1->partp != (tagPART *)0x0) && (param_1->partp->id == param_1->partid)) {
    return 1;
  }
  PartId_Clear(param_1);
  return 0;
}
