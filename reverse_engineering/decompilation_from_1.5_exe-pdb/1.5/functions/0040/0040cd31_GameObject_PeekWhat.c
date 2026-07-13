/*
 * Entry: 0040cd31
 * Name: GameObject::PeekWhat
 * Namespace: GameObject
 * Signature: AiCommand PeekWhat(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiCommand __thiscall GameObject::PeekWhat(GameObject *this)

{
  return (this->nextCmd).what;
}
