/*
 * Entry: 00410725
 * Name: GameObjectClass::GetBoundingSphere
 * Namespace: GameObjectClass
 * Signature: SPHERE * GetBoundingSphere(GameObjectClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

SPHERE * __thiscall GameObjectClass::GetBoundingSphere(GameObjectClass *this)

{
  if ((this->bSphere).radius < 0.0) {
    InitBoundingData(this);
  }
  return &this->bSphere;
}
