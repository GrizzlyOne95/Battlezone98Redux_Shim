/*
 * Entry: 0054e5a0
 * Name: mh_No
 * Namespace: Global
 * Signature: long mh_No(_menu_item * param_1, MENU_CMD param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl mh_No(_menu_item *param_1,MENU_CMD param_2)

{
  long *plVar1;
  int iVar2;
  _menu_item *p_Var3;
  
  if ((3 < (int)param_2) && (((int)param_2 < 6 || (param_2 == MC_REJECT)))) {
    p_Var3 = (mInfo.curMenu)->items;
    iVar2 = 0;
    plVar1 = &(mInfo.curMenu)->numItems;
    if (0 < *plVar1) {
      do {
        if ((p_Var3->handlerFunc != (_func___cdecl_long__menu_item_ptr_MENU_CMD *)0x0) &&
           ((p_Var3->flags & 2) == 0)) {
          (*p_Var3->handlerFunc)(p_Var3,MC_REJECT);
        }
        iVar2 = iVar2 + 1;
        p_Var3 = p_Var3 + 1;
      } while (iVar2 < *plVar1);
    }
    mInfo.returnVal = 0;
    iVar2 = OpenMenu((mInfo.curMenu)->parent);
    return iVar2;
  }
  return 1;
}
