/*
 * Entry: 0045e0fd
 * Name: CameraCancelled
 * Namespace: Global
 * Signature: bool CameraCancelled(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CameraCancelled(void)

{
  bool bVar1;
  float fVar2;
  
  cameraCallCount = 0;
  if (loadInCamera) {
    return true;
  }
  if (!cameraReady) {
    cameraCallCount = 0;
    return false;
  }
  fVar2 = Get_Time();
  if (cancelEnableTime <= fVar2) {
    if (user_controls.key != 0x20) {
      return false;
    }
    fVar2 = Get_Time();
    cancelEnableTime = fVar2 + 1.5;
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  user_controls.key = 0;
  return bVar1;
}
