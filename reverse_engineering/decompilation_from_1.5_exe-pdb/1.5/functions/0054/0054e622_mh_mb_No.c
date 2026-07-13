/*
 * Entry: 0054e622
 * Name: mh_mb_No
 * Namespace: Global
 * Signature: long mh_mb_No(_menu_item * param_1, MENU_CMD param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl mh_mb_No(_menu_item *param_1,MENU_CMD param_2)

{
  int iVar1;
  
  if (param_2 == MC_ENTER) {
    mInfo.returnVal = 2;
    iVar1 = OpenMenu((mInfo.curMenu)->parent);
    return iVar1;
  }
  return 0;
}
