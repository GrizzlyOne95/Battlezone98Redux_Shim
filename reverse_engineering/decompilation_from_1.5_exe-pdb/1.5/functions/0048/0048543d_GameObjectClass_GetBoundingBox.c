/*
 * Entry: 0048543d
 * Name: GameObjectClass::GetBoundingBox
 * Namespace: GameObjectClass
 * Signature: BBOX * GetBoundingBox(GameObjectClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BBOX * __thiscall GameObjectClass::GetBoundingBox(GameObjectClass *this)

{
  if ((this->bSphere).radius < 0.0) {
    InitBoundingData(this);
  }
  return &this->bBox;
}
