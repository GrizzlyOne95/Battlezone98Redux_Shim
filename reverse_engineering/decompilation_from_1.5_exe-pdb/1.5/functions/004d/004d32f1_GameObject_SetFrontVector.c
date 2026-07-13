/*
 * Entry: 004d32f1
 * Name: GameObject::SetFrontVector
 * Namespace: GameObject
 * Signature: void SetFrontVector(GameObject * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetFrontVector(GameObject *this,VECTOR_3D *param_1)

{
  float *pfVar1;
  _OBJ76 *p_Var2;
  VECTOR_3D *pVVar3;
  MAT_3D *pMVar4;
  VECTOR_3D local_20;
  float local_14;
  float fStack_10;
  float fStack_c;
  float *local_8;
  
  p_Var2 = this->obj;
  pMVar4 = &p_Var2->transform;
  pVVar3 = Normalize_Vector(&local_20,param_1);
  local_14 = pVVar3->x;
  fStack_10 = pVVar3->y;
  fStack_c = pVVar3->z;
  pfVar1 = &(p_Var2->transform).front_x;
  *pfVar1 = local_14;
  local_8 = &(p_Var2->transform).up_x;
  (p_Var2->transform).front_y = fStack_10;
  (p_Var2->transform).front_z = fStack_c;
  pVVar3 = Cross_Product(&local_20,(VECTOR_3D *)local_8,(VECTOR_3D *)pfVar1);
  pMVar4->right_x = pVVar3->x;
  (p_Var2->transform).right_y = pVVar3->y;
  (p_Var2->transform).right_z = pVVar3->z;
  pVVar3 = Normalize_Vector(&local_20,(VECTOR_3D *)pMVar4);
  pMVar4->right_x = pVVar3->x;
  (p_Var2->transform).right_y = pVVar3->y;
  (p_Var2->transform).right_z = pVVar3->z;
  pVVar3 = Cross_Product(&local_20,(VECTOR_3D *)pfVar1,(VECTOR_3D *)pMVar4);
  *local_8 = pVVar3->x;
  local_8[1] = pVVar3->y;
  local_8[2] = pVVar3->z;
  return;
}
