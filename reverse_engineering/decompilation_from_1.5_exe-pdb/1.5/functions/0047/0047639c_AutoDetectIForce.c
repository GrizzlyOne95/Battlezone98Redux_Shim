/*
 * Entry: 0047639c
 * Name: AutoDetectIForce
 * Namespace: Global
 * Signature: int AutoDetectIForce(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl AutoDetectIForce(void)

{
  Bool BVar1;
  int iVar2;
  
  iVar2 = 1;
  do {
    (*pSetJoystickPort)(iVar2);
    BVar1 = (*pInitStick)(&StickRec);
    if (BVar1 != False) {
      return 1;
    }
    (*pCloseStick)();
    iVar2 = iVar2 + 1;
  } while (iVar2 < 5);
  return 0;
}
