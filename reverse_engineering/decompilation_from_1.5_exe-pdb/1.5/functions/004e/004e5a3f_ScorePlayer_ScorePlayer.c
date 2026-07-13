/*
 * Entry: 004e5a3f
 * Name: ScorePlayer::ScorePlayer
 * Namespace: ScorePlayer
 * Signature: ScorePlayer * ScorePlayer(ScorePlayer * this, ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

ScorePlayer * __thiscall ScorePlayer::ScorePlayer(ScorePlayer *this,ushort param_1)

{
  int iVar1;
  ScorePlayer *extraout_EAX;
  undefined2 in_stack_00000006;
  int iVar2;
  ScorePlayer *local_24;
  int local_20;
  char local_1c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  this->dpid = param_1;
  if (Net::dp != (dp_s *)0x0) {
    iVar1 = dpGetPlayerName(Net::dp,_param_1,this->caName);
    if (iVar1 != 0) {
      this->caName[0] = '\0';
    }
    this->caName[0x18] = '\0';
    local_20 = 0x10;
    iVar1 = dpGetPlayerBlob(Net::dp,_param_1);
    if ((iVar1 == 0) && (local_20 != 0)) {
      this->iTeam = (int)local_1c & 0xf;
      sprintf(this->caTeam,"%d");
    }
    else {
      this->iTeam = 0;
      this->caTeam[0] = '?';
      this->caTeam[1] = '\0';
    }
    iVar2 = 4;
    local_20 = iVar2;
    iVar1 = dpGetPlayerData(Net::dp,_param_1,0xf,&this->iKills,&local_20);
    if ((((iVar1 != 0) || (local_20 != 4)) || (this->iKills < 0)) || (99999 < this->iKills)) {
      this->iKills = 0;
    }
    sprintf(this->caKills,"%d");
    local_20 = iVar2;
    iVar1 = dpGetPlayerData(Net::dp,_param_1,0x10,&this->iDeaths,&local_20,0);
    if (((iVar1 != 0) || (local_20 != 4)) || ((this->iDeaths < 0 || (99999 < this->iDeaths)))) {
      this->iDeaths = 0;
    }
    sprintf(this->caDeaths,"%d");
    local_20 = iVar2;
    iVar1 = dpGetPlayerData(Net::dp,_param_1,0x11,&this->fStartTime,&local_20,0);
    if (((iVar1 != 0) || (local_20 != 4)) ||
       ((this->fStartTime < 0.0 || (99999.0 < this->fStartTime)))) {
      this->fStartTime = 0.0;
    }
    sprintf(this->caStartTime,"%5.2f",(double)this->fStartTime);
    local_20 = iVar2;
    iVar1 = dpGetPlayerData(Net::dp,_param_1,0x12,&this->fTimeInZone,&local_20,0);
    if ((((iVar1 != 0) || (local_20 != 4)) || (this->fTimeInZone < 0.0)) ||
       (99999.0 < this->fTimeInZone)) {
      this->fTimeInZone = 0.0;
    }
    _ftol2();
    local_24 = extraout_EAX;
    _ftol2();
    sprintf(this->caTimeInZone,"%02d:%02d",local_24);
    local_20 = iVar2;
    iVar1 = dpGetPlayerData(Net::dp,_param_1,0x13,&this->iLives,&local_20,0);
    if (((iVar1 != 0) || (local_20 != 4)) || ((this->iLives < 0 || (99999 < this->iLives)))) {
      this->iLives = Net::iStartLivesLeft;
    }
    sprintf(this->caLives,"%d");
  }
  local_24 = this;
  std::vector<ScorePlayer_*,std::allocator<ScorePlayer_*>_>::push_back(&playerV,&local_24);
  return this;
}
