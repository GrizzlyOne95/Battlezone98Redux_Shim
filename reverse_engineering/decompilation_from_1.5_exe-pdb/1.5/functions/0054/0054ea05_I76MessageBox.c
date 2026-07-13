/*
 * Entry: 0054ea05
 * Name: I76MessageBox
 * Namespace: Global
 * Signature: long I76MessageBox(char * param_1, char * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl I76MessageBox(char *param_1,char *param_2,long param_3)

{
  char *in_EAX;
  int iVar1;
  
  if (((uint)param_2 & 1) != 0) {
    m_MessageBox.items = mi_MessageBox2Choice;
    m_MessageBox.numItems = 4;
    mi_MessageBox2Choice[1].itemText = param_1;
    m_MessageBox.curItem = 2;
    mi_MessageBox2Choice[0].itemText = in_EAX;
    iVar1 = InitMenu(&m_MessageBox,ExitI76MessageBox);
    if (iVar1 != 0) {
      PauseGAS();
      SetScreenMode(SCREENMODE_MENU);
      while (ScreenMode == SCREENMODE_MENU) {
        HandleGamePauses(WeAreActive);
      }
      return mInfo.returnVal;
    }
  }
  return 0;
}
