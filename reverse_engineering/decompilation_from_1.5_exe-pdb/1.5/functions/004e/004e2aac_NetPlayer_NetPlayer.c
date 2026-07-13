/*
 * Entry: 004e2aac
 * Name: NetPlayer::NetPlayer
 * Namespace: NetPlayer
 * Signature: NetPlayer * NetPlayer(NetPlayer * this, ushort param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

NetPlayer * __thiscall
NetPlayer::NetPlayer(NetPlayer *this,ushort param_1,char *param_2,int param_3)

{
  char cVar1;
  NetPlayer **ppNVar2;
  char *pcVar3;
  
  this->flagIndex = 0;
  this->dwJoinTime = 0;
  this->dwLaggingTime = 0;
  this->dwNewestSendTime = 0;
  this->bGotFlag = false;
  ppNVar2 = std::
            map<unsigned_short,NetPlayer_*,std::less<unsigned_short>,std::allocator<std::pair<unsigned_short_const_,NetPlayer_*>_>_>
            ::operator[](&netPlayerMap,&param_1);
  *ppNVar2 = this;
  this->playerId = param_1;
  pcVar3 = param_2;
  do {
    cVar1 = *pcVar3;
    pcVar3[(int)this + (0x13a - (int)param_2)] = cVar1;
    pcVar3 = pcVar3 + 1;
  } while (cVar1 != '\0');
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
  SetTeam(this,param_3);
  this->dwPingReplies = 0xffffffff;
  return this;
}
