/*
 * Entry: 004955d5
 * Name: GameObject::CanCommand
 * Namespace: GameObject
 * Signature: bool CanCommand(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GameObject::CanCommand(GameObject *this)

{
  if (((this != userObject) && ((this->obj->flags & 0x200) == 0)) &&
     (this->aiProcess != (AiProcess *)0x0)) {
    return (this->curCmd).priority == 0;
  }
  return false;
}
