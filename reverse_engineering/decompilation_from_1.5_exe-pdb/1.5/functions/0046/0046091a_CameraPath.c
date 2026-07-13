/*
 * Entry: 0046091a
 * Name: CameraPath
 * Namespace: Global
 * Signature: bool CameraPath(char * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CameraPath(char *param_1,int param_2,int param_3,int param_4)

{
  AiPath *pAVar1;
  GameObject *pGVar2;
  _OBJ76 *p_Var3;
  int iVar4;
  
  if (loadInCamera) {
    return true;
  }
  cameraCallCount = cameraCallCount + 1;
  pAVar1 = AiPath::Find(param_1);
  pGVar2 = GameObjectHandle::GetObj(param_4);
  if (pGVar2 != (GameObject *)0x0) {
    p_Var3 = (_OBJ76 *)(**(code **)(pGVar2->_padding_ + 0x30))();
    fsm_camera_trans_obj(pAVar1,&param_2,&param_3,p_Var3);
  }
  iVar4 = cameraIsArrived();
  return (bool)('\x01' - (iVar4 != 1));
}
