/*
 * Entry: 0045e0a4
 * Name: PanDone
 * Namespace: Global
 * Signature: bool PanDone(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PanDone(void)

{
  int iVar1;
  
  if (loadInCamera) {
    return true;
  }
  iVar1 = cameraIsArrived();
  return (bool)('\x01' - (iVar1 != 1));
}
