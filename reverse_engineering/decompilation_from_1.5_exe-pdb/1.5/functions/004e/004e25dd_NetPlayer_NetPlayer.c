/*
 * Entry: 004e25dd
 * Name: NetPlayer::NetPlayer
 * Namespace: NetPlayer
 * Signature: NetPlayer * NetPlayer(NetPlayer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

NetPlayer * __thiscall NetPlayer::NetPlayer(NetPlayer *this)

{
  int iVar1;
  
  this->flagIndex = 0;
  this->dwJoinTime = 0;
  this->dwLaggingTime = 0;
  this->dwNewestSendTime = 0;
  this->bGotFlag = false;
  this->playerId = 0xfa01;
  this->playerName[0] = '\0';
  this->waitingForSpawnPoint = true;
  this->SpawnPointer = (SpawnPoint *)0x0;
  this->offset = 0;
  this->BAddOffset = 1;
  this->delay = 1000000;
  this->bClockInitialized = false;
  this->iHistQueuePointer = 0;
  this->iHistQueueSize = 0;
  this->deaths = 0;
  this->kills = 0;
  this->bGotSyncPacket = false;
  this->bGotSyncPacketAck = false;
  this->bTeamNumber = '\0';
  iVar1 = FindUnusedTeam();
  SetTeam(this,iVar1);
  this->dwPingReplies = 0xffffffff;
  return this;
}
