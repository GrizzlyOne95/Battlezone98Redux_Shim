/*
 * Entry: 0045e477
 * Name: GameObject::SetOrigin
 * Namespace: GameObject
 * Signature: void SetOrigin(GameObject * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetOrigin(GameObject *this,VECTOR_3D *param_1)

{
  _OBJ76 *p_Var1;
  
  p_Var1 = this->obj;
  (p_Var1->transform).posit_x = (double)param_1->x;
  (p_Var1->transform).posit_y = (double)param_1->y;
  (p_Var1->transform).posit_z = (double)param_1->z;
  UpdatePosition(this);
  return;
}
