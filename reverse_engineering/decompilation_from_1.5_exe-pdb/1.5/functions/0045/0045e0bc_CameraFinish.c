/*
 * Entry: 0045e0bc
 * Name: CameraFinish
 * Namespace: Global
 * Signature: bool CameraFinish(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CameraFinish(void)

{
  int iVar1;
  
  if (loadInCamera) goto LAB_0045e0d7;
  while( true ) {
    fsm_pop_camera();
LAB_0045e0d7:
    iVar1 = isCineractive();
    if (iVar1 == 0) break;
    Trace("fsm_pop_camera called again\n");
  }
  EnableInputs();
  cameraCallCount = 0;
  cameraReady = false;
  loadInCamera = false;
  return true;
}
