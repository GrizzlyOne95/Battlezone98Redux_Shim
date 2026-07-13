/*
 * Entry: 004e7432
 * Name: AnimObj_Status
 * Namespace: Global
 * Signature: long AnimObj_Status(int param_1, tagANIMOBJ_ACTIVE_LIST * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_Status(int param_1,tagANIMOBJ_ACTIVE_LIST **param_2)

{
  if (((uint)param_1 < 0x200) && (AnimActiveList[param_1].status != 0)) {
    if (param_2 != (tagANIMOBJ_ACTIVE_LIST **)0x0) {
      *param_2 = AnimActiveList + param_1;
    }
    return 0;
  }
  if (param_2 != (tagANIMOBJ_ACTIVE_LIST **)0x0) {
    *param_2 = (tagANIMOBJ_ACTIVE_LIST *)0x0;
  }
  return -1;
}
