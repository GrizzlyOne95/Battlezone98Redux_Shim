/*
 * Entry: 0052fed0
 * Name: Grenade::Simulate
 * Namespace: Grenade
 * Signature: void Simulate(Grenade * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Grenade::Simulate(Grenade *this,float param_1)

{
  VECTOR_3D VVar1;
  float fVar2;
  
  *(float *)&this->field_0x38 = *(float *)&this->field_0x38 - param_1 * 4.9;
  Rocket::Simulate((Rocket *)this,param_1);
  *(float *)&this->field_0x38 = *(float *)&this->field_0x38 - param_1 * 4.9;
  VVar1.x = *(float *)&this->field_0x34;
  VVar1.y = *(float *)&this->field_0x38;
  VVar1.z = *(float *)&this->field_0x3c;
  fVar2 = VecLen(VVar1);
  *(float *)&this->field_0x24 = fVar2;
  if (fVar2 <= 0.0) {
    fVar2 = 1e+30;
  }
  else {
    fVar2 = 1.0 / fVar2;
  }
  *(float *)&this->field_0x28 = fVar2;
  Ordnance::OrientToVelocity((Ordnance *)this);
  return;
}
