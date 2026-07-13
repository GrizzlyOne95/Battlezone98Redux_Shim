/*
 * Entry: 0047bcfb
 * Name: GameObject::GetClass
 * Namespace: GameObject
 * Signature: GameObjectClass * GetClass(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectClass * __thiscall GameObject::GetClass(GameObject *this)

{
  return (GameObjectClass *)(this->nextCmd).who;
}
