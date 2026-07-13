/*
 * Entry: 004dd42f
 * Name: Net::HandleSpawnPoint
 * Namespace: Net
 * Signature: void HandleSpawnPoint(Net * this, SPAWNPOINT_PACKET * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Net::HandleSpawnPoint(Net *this,SPAWNPOINT_PACKET *param_1)

{
  NetState NVar1;
  NetPlayer *this_00;
  
  NVar1 = this->state;
  (this->start_location).x = (param_1->location).x;
  (this->start_location).y = (param_1->location).y;
  (this->start_location).z = (param_1->location).z;
  if (NVar1 == WAITING_FOR_SPAWNPOINT) {
    this->state = NET_IS_RUNNING;
  }
  this->got_start_location = true;
  Team = (int)param_1->bTeamNumber;
  this_00 = NetPlayer::Find(myPlayerID);
  if (this_00 != (NetPlayer *)0x0) {
    NetPlayer::SetWaitingForSpawnPoint(this_00,false);
    NetPlayer::SetTeam(this_00,(uint)param_1->bTeamNumber);
  }
  return;
}
