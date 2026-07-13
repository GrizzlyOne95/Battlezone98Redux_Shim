/*
 * Entry: 004e7486
 * Name: AnimObj_Stop
 * Namespace: Global
 * Signature: long AnimObj_Stop(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl AnimObj_Stop(int param_1)

{
  int iVar1;
  tagANIMOBJ_ACTIVE_LIST *ptVar2;
  
  if ((uint)param_1 < 0x200) {
    if (AnimObj_ActiveCount < 1) {
      AnimObj_ActiveCount = 0;
    }
    else {
      AnimObj_ActiveCount = AnimObj_ActiveCount + -1;
    }
    ptVar2 = AnimActiveList + param_1;
    for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
      ptVar2->status = 0;
      ptVar2 = (tagANIMOBJ_ACTIVE_LIST *)&ptVar2->animHeader;
    }
    return 0;
  }
  return -1;
}
