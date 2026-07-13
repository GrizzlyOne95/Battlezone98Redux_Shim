/*
 * Entry: 0044c929
 * Name: GameObject::SetTransform
 * Namespace: GameObject
 * Signature: void SetTransform(GameObject * this, MAT_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetTransform(GameObject *this,MAT_3D *param_1)

{
  int iVar1;
  MAT_3D *pMVar2;
  
  pMVar2 = &this->obj->transform;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar2->right_x = param_1->right_x;
    param_1 = (MAT_3D *)&param_1->right_y;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
  }
  UpdatePosition(this);
  return;
}
