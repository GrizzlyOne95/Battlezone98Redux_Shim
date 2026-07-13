/*
 * Entry: 00514fde
 * Name: PartId_Clear
 * Namespace: Global
 * Signature: void PartId_Clear(tagPARTID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PartId_Clear(tagPARTID *param_1)

{
  Debug_Assert((int)param_1,0xe,".\\Schedule\\Partid.c","pid");
  param_1->partid = -1;
  param_1->partp = (tagPART *)0x0;
  return;
}
