/*
 * Entry: 0045e49d
 * Name: GameObject::SetVelocity
 * Namespace: GameObject
 * Signature: void SetVelocity(GameObject * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetVelocity(GameObject *this,VECTOR_3D *param_1)

{
  float fVar1;
  
  (this->euler).v.x = param_1->x;
  (this->euler).v.y = param_1->y;
  (this->euler).v.z = param_1->z;
  fVar1 = VecLen(*param_1);
  (this->euler).v_mag = fVar1;
  if (fVar1 <= 0.0) {
    fVar1 = 1e+30;
  }
  else {
    fVar1 = 1.0 / fVar1;
  }
  (this->euler).v_mag_inv = fVar1;
  return;
}
