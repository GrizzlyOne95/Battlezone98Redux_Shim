/*
 * Entry: 004860a4
 * Name: Craft::AddHealth
 * Namespace: Craft
 * Signature: void AddHealth(Craft * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Craft::AddHealth(Craft *this,float param_1)

{
  GameObject::AddHealth((GameObject *)this,param_1);
  (*(code *)this[-1].smokeList[4]->parent)(this->_padding_);
  return;
}
