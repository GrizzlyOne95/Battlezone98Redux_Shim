/*
 * Entry: 0050e3f3
 * Name: BuildId_Valid
 * Namespace: Global
 * Signature: int BuildId_Valid(tagBUILDID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildId_Valid(tagBUILDID *param_1)

{
  Debug_Assert((int)param_1,0x26,".\\Schedule\\Buildid.c","bid");
  if ((param_1->buildp != (tagBUILDING *)0x0) && (param_1->buildp->id == param_1->buildid)) {
    return 1;
  }
  BuildId_Clear(param_1);
  return 0;
}
