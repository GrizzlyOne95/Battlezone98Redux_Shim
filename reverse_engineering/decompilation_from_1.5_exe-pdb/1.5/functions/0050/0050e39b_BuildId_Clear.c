/*
 * Entry: 0050e39b
 * Name: BuildId_Clear
 * Namespace: Global
 * Signature: void BuildId_Clear(tagBUILDID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildId_Clear(tagBUILDID *param_1)

{
  Debug_Assert((int)param_1,0xf,".\\Schedule\\Buildid.c","bid");
  param_1->buildid = -1;
  param_1->buildp = (tagBUILDING *)0x0;
  return;
}
