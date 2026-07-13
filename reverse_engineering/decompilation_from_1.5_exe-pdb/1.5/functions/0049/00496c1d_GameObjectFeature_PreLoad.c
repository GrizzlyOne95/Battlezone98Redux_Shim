/*
 * Entry: 00496c1d
 * Name: GameObjectFeature::PreLoad
 * Namespace: GameObjectFeature
 * Signature: void PreLoad(GameObjectFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObjectFeature::PreLoad(GameObjectFeature *this)

{
  GameObject::InitHandles();
  this->maxSize = 0;
  GameObject::objectiveCount = 0;
  GameObject::userObject = (GameObject *)0x0;
  GameObject::userTeamNumber = 0;
  GameObject::userTeamList = (Team *)0x0;
  return;
}
