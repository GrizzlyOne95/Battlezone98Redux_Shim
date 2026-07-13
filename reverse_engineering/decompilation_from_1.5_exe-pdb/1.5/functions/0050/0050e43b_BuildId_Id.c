/*
 * Entry: 0050e43b
 * Name: BuildId_Id
 * Namespace: Global
 * Signature: int BuildId_Id(tagBUILDID * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BuildId_Id(tagBUILDID *param_1)

{
  BuildId_Valid(param_1);
  return param_1->buildid;
}
