/*
 * Entry: 0045e4ee
 * Name: GameObject::SetCurHealth
 * Namespace: GameObject
 * Signature: void SetCurHealth(GameObject * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetCurHealth(GameObject *this,float param_1)

{
  this->curHealth = param_1;
  if (0.0 < this->maxHealth) {
    this->healthRatio = param_1 / this->maxHealth;
  }
  return;
}
