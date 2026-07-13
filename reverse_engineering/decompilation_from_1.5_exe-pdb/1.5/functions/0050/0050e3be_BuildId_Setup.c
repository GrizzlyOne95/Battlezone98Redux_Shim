/*
 * Entry: 0050e3be
 * Name: BuildId_Setup
 * Namespace: Global
 * Signature: void BuildId_Setup(tagBUILDID * param_1, tagBUILDING * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl BuildId_Setup(tagBUILDID *param_1,tagBUILDING *param_2)

{
  Debug_Assert((int)param_1,0x17,".\\Schedule\\Buildid.c","bid");
  if (param_2 != (tagBUILDING *)0x0) {
    param_1->buildid = param_2->id;
    param_1->buildp = param_2;
    return;
  }
  BuildId_Clear(param_1);
  return;
}
