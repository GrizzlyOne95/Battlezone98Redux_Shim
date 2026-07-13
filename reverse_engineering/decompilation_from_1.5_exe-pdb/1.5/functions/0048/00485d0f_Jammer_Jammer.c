/*
 * Entry: 00485d0f
 * Name: Jammer::Jammer
 * Namespace: Jammer
 * Signature: Jammer * Jammer(Jammer * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Jammer * __thiscall Jammer::Jammer(Jammer *this,GameObject *param_1)

{
  this->maxSpeed = 0.0;
  this->owner = param_1;
  return this;
}
