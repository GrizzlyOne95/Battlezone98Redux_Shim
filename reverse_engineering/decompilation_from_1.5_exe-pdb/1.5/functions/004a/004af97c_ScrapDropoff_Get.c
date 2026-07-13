/*
 * Entry: 004af97c
 * Name: ScrapDropoff_Get
 * Namespace: Global
 * Signature: void ScrapDropoff_Get(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ScrapDropoff_Get(int param_1)

{
  dropoffList[param_1].refCount = dropoffList[param_1].refCount + -1;
  if (dropoffList[param_1].dropObj != (ScrapDropoff *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x004af998. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*(int *)&(dropoffList[param_1].dropObj)->field_0x20 + 0x10))();
    return;
  }
  return;
}
