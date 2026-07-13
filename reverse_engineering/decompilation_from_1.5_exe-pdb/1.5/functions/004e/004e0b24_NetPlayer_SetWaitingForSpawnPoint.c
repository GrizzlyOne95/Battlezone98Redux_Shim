/*
 * Entry: 004e0b24
 * Name: NetPlayer::SetWaitingForSpawnPoint
 * Namespace: NetPlayer
 * Signature: void SetWaitingForSpawnPoint(NetPlayer * this, bool param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall NetPlayer::SetWaitingForSpawnPoint(NetPlayer *this,bool param_1)

{
  this->waitingForSpawnPoint = param_1;
  return;
}
