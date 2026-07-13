/*
 * Entry: 004803fd
 * Name: AudioMessageMgr::RepeatLast
 * Namespace: AudioMessageMgr
 * Signature: void RepeatLast(AudioMessageMgr * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AudioMessageMgr::RepeatLast(AudioMessageMgr *this)

{
  if (this->lastMsg[0] != '\0') {
    Insert(this,this->lastMsg);
  }
  return;
}
