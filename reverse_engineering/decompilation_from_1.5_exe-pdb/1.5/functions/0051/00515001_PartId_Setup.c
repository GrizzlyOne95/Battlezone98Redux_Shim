/*
 * Entry: 00515001
 * Name: PartId_Setup
 * Namespace: Global
 * Signature: void PartId_Setup(tagPARTID * param_1, tagPART * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl PartId_Setup(tagPARTID *param_1,tagPART *param_2)

{
  Debug_Assert((int)param_1,0x16,".\\Schedule\\Partid.c","pid");
  param_1->partid = param_2->id;
  param_1->partp = param_2;
  return;
}
