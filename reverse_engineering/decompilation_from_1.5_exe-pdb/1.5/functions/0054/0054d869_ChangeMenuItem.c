/*
 * Entry: 0054d869
 * Name: ChangeMenuItem
 * Namespace: Global
 * Signature: long ChangeMenuItem(long param_1, long param_2, MENU_CMD param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl ChangeMenuItem(long param_1,long param_2,MENU_CMD param_3,long param_4)

{
  long lVar1;
  
  if (param_2 == 1) {
    return 0;
  }
  if (param_3 == MC_INC_ITEM) {
LAB_0054d8ab:
    lVar1 = param_1 + 1;
    if (param_2 <= lVar1) {
      if ((param_4 & 0x180U) != 0) {
        return param_1;
      }
      return (uint)param_4 >> 0xc & 1;
    }
  }
  else {
    if (param_3 != MC_DEC_ITEM) {
      if (param_3 == MC_INC_VALUE) goto LAB_0054d8ab;
      if (param_3 != MC_DEC_VALUE) {
        return param_1;
      }
    }
    lVar1 = param_1 + -1;
    if (lVar1 < (int)((uint)param_4 >> 0xc & 1)) {
      if ((param_4 & 0x180U) != 0) {
        return param_1;
      }
      return param_2 + -1;
    }
  }
  return lVar1;
}
