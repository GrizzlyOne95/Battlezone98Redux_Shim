/*
 * Entry: 0045e518
 * Name: GameObject::SetMaxHealth
 * Namespace: GameObject
 * Signature: void SetMaxHealth(GameObject * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObject::SetMaxHealth(GameObject *this,float param_1)

{
  this->maxHealth = param_1;
  if (0.0 < param_1) {
    this->healthRatio = this->curHealth / param_1;
  }
  return;
}
