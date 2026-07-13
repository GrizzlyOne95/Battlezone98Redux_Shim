/*
 * Entry: 004e0cc5
 * Name: NetPlayer::RecordDeath
 * Namespace: NetPlayer
 * Signature: void RecordDeath(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NetPlayer::RecordDeath(int param_1,int param_2)

{
  NetPlayer *pNVar1;
  bool bVar2;
  ushort uVar3;
  Team *this;
  
  uVar3 = Net_GetMyPlayerID();
  if ((0 < param_1) && (pNVar1 = netPlayerByTeam[param_1], pNVar1 != (NetPlayer *)0x0)) {
    if (uVar3 == pNVar1->playerId) {
      Increment_Player_Deaths();
    }
    pNVar1->deaths = pNVar1->deaths + 1;
  }
  if (0 < param_2) {
    this = Team::GetTeam(param_2);
    bVar2 = Team::FriendP(this,param_1);
    if (!bVar2) {
      pNVar1 = netPlayerByTeam[param_2];
      if (pNVar1 == (NetPlayer *)0x0) {
        Net::SendKill(uVar3,0xfa01,param_2);
      }
      else {
        if (uVar3 == pNVar1->playerId) {
          Increment_Player_Kills();
        }
        else {
          Net::SendKill(uVar3,pNVar1->playerId,param_2);
        }
        pNVar1->kills = pNVar1->kills + 1;
      }
    }
  }
  return;
}
