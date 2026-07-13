/*
 * Entry: 004dd92f
 * Name: Net_KillPlayer
 * Namespace: Global
 * Signature: void Net_KillPlayer(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_KillPlayer(void)

{
  float fVar1;
  float fVar2;
  
  if ((!Net::deathmatch) && (respawn != 1)) {
    Net::iLivesLeft = Net::iLivesLeft + -1;
    Decrement_Player_Lives();
  }
  if (Net::iLivesLeft < 1) {
    fVar1 = 5.0;
  }
  else {
    fVar1 = 2.0;
  }
  fVar2 = Get_TimeLocal();
  respawn = 1;
  respawn_timer = fVar2 + fVar1;
  return;
}
