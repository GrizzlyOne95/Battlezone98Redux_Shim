/*
 * Entry: 004059f1
 * Name: GameObject::GetHandle
 * Namespace: GameObject
 * Signature: int GetHandle(GameObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __thiscall GameObject::GetHandle(GameObject *this)

{
  if (this->seqNo == 0) {
    return 0;
  }
  return this->indexNo << 0x17 | this->seqNo & 0x7fffffU;
}
