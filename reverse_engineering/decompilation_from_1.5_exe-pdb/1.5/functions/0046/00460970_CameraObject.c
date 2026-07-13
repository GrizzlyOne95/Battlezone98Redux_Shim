/*
 * Entry: 00460970
 * Name: CameraObject
 * Namespace: Global
 * Signature: bool CameraObject(int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CameraObject(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  bool bVar1;
  GameObject *pGVar2;
  GameObject *pGVar3;
  _OBJ76 *p_Var4;
  _OBJ76 *p_Var5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  
  if (loadInCamera) {
    return true;
  }
  cameraCallCount = cameraCallCount + 1;
  pGVar2 = GameObjectHandle::GetObj(param_5);
  pGVar3 = GameObjectHandle::GetObj(param_1);
  if ((pGVar2 == (GameObject *)0x0) || (pGVar3 == (GameObject *)0x0)) {
    bVar1 = true;
  }
  else {
    p_Var4 = (_OBJ76 *)(**(code **)(pGVar2->_padding_ + 0x30))();
    piVar8 = &param_4;
    piVar7 = &param_3;
    piVar6 = &param_2;
    p_Var5 = (_OBJ76 *)(**(code **)(pGVar3->_padding_ + 0x30))();
    fsm_camera_obj_obj(p_Var5,piVar6,piVar7,piVar8,p_Var4);
    bVar1 = false;
  }
  return bVar1;
}
