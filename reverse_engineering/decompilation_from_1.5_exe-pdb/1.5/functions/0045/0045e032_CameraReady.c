/*
 * Entry: 0045e032
 * Name: CameraReady
 * Namespace: Global
 * Signature: bool CameraReady(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CameraReady(void)

{
  float fVar1;
  
  cameraCallCount = 0;
  cameraReady = true;
  loadInCamera = false;
  fVar1 = Get_Time();
  cancelEnableTime = fVar1 + 1.5;
  fsm_push_camera();
  DisableInputs();
  return true;
}
