/*
 * Entry: 0047bd02
 * Name: GameObject::GetTeam
 * Namespace: GameObject
 * Signature: int GetTeam(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall GameObject::GetTeam(GameObject *this)

{
  return (int)(this->euler).Alpha.y;
}
