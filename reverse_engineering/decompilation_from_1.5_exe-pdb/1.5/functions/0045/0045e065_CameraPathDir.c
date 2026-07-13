/*
 * Entry: 0045e065
 * Name: CameraPathDir
 * Namespace: Global
 * Signature: bool CameraPathDir(char * param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CameraPathDir(char *param_1,int param_2,int param_3)

{
  AiPath *pAVar1;
  int iVar2;
  
  if (loadInCamera) {
    return true;
  }
  cameraCallCount = cameraCallCount + 1;
  pAVar1 = AiPath::Find(param_1);
  if (pAVar1 != (AiPath *)0x0) {
    fsm_camera_trans_path_dir(pAVar1,&param_2,&param_3);
  }
  iVar2 = cameraIsArrived();
  return (bool)('\x01' - (iVar2 != 1));
}
