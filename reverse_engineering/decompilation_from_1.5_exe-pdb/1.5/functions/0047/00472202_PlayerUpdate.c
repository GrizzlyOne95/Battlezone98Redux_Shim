/*
 * Entry: 00472202
 * Name: PlayerUpdate
 * Namespace: Global
 * Signature: int PlayerUpdate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl PlayerUpdate(void)

{
  int iVar1;
  int iVar2;
  Disc *unaff_ESI;
  int iVar3;
  
  iVar3 = 0;
  if ((CD_OK == 0) || (iVar1 = PlayerState(), iVar1 == pState)) {
LAB_00472259:
    iVar3 = 0;
  }
  else {
    if ((iVar1 != 1) && ((iVar1 == 2 && (pState == 1)))) {
      do {
        iVar2 = pDiscInit(unaff_ESI);
        if (iVar2 == 0) break;
        _putch(7);
        iVar3 = iVar3 + 1;
      } while (iVar3 < 3);
      if (iVar3 == 3) goto LAB_00472259;
    }
    iVar3 = 1;
    pState = iVar1;
  }
  return iVar3;
}
