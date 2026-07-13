/*
 * Entry: 0050e42b
 * Name: BuildId_Ptr
 * Namespace: Global
 * Signature: tagBUILDING * BuildId_Ptr(tagBUILDID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

tagBUILDING * __cdecl BuildId_Ptr(tagBUILDID *param_1)

{
  BuildId_Valid(param_1);
  return param_1->buildp;
}
