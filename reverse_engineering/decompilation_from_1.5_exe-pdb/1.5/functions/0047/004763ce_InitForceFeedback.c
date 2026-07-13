/*
 * Entry: 004763ce
 * Name: InitForceFeedback
 * Namespace: Global
 * Signature: void InitForceFeedback(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitForceFeedback(void)

{
  Bool BVar1;
  int iVar2;
  
  ForceFeedbackPresent = 0;
  if (ForceFeedbackAllowed != 0) {
    BVar1 = IForceInit();
    if (BVar1 != False) {
      iVar2 = 1;
      while( true ) {
        (*pSetJoystickPort)(iVar2);
        BVar1 = (*pInitStick)(&StickRec);
        if (BVar1 != False) break;
        (*pCloseStick)();
        iVar2 = iVar2 + 1;
        if (4 < iVar2) {
          IForceEnd();
          return;
        }
      }
      gear = -1;
      ForceFeedbackPresent = 1;
    }
  }
  return;
}
