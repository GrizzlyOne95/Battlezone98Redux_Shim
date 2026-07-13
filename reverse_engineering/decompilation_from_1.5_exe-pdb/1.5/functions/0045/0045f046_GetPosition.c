/*
 * Entry: 0045f046
 * Name: GetPosition
 * Namespace: Global
 * Signature: VECTOR_3D * GetPosition(VECTOR_3D * __return_storage_ptr__, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

VECTOR_3D * __cdecl GetPosition(VECTOR_3D *__return_storage_ptr__,int param_1)

{
  _OBJ76 *p_Var1;
  float fVar2;
  GameObject *pGVar3;
  float local_10;
  float local_c;
  
  pGVar3 = GameObjectHandle::GetObj(param_1);
  if (pGVar3 == (GameObject *)0x0) {
    fVar2 = 0.0;
    local_10 = 0.0;
    local_c = 0.0;
  }
  else {
    p_Var1 = pGVar3->obj;
    local_10 = (float)(p_Var1->transform).posit_x;
    local_c = (float)(p_Var1->transform).posit_y;
    fVar2 = (float)(p_Var1->transform).posit_z;
  }
  __return_storage_ptr__->x = local_10;
  __return_storage_ptr__->y = local_c;
  __return_storage_ptr__->z = fVar2;
  return __return_storage_ptr__;
}
