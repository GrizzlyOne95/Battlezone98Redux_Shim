/*
 * Entry: 004869c7
 * Name: GameObject::AddVelocity
 * Namespace: GameObject
 * Signature: void AddVelocity(GameObject * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::AddVelocity(GameObject *this,VECTOR_3D *param_1)

{
  VECTOR_3D *pVVar1;
  float *pfVar2;
  float fVar3;
  
  pVVar1 = &(this->euler).v;
  pfVar2 = &(this->euler).v.y;
  pVVar1->x = param_1->x + pVVar1->x;
  *pfVar2 = param_1->y + *pfVar2;
  pfVar2 = &(this->euler).v.z;
  *pfVar2 = param_1->z + *pfVar2;
  fVar3 = VecLen(*pVVar1);
  (this->euler).v_mag = fVar3;
  if (fVar3 <= 0.0) {
    fVar3 = 1e+30;
  }
  else {
    fVar3 = 1.0 / fVar3;
  }
  (this->euler).v_mag_inv = fVar3;
  return;
}
