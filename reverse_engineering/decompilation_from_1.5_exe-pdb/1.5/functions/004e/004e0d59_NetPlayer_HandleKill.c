/*
 * Entry: 004e0d59
 * Name: NetPlayer::HandleKill
 * Namespace: NetPlayer
 * Signature: void HandleKill(int param_1, KILL_PACKET * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl NetPlayer::HandleKill(int param_1,KILL_PACKET *param_2)

{
  ulong *puVar1;
  
  if ((0 < param_1) && (netPlayerByTeam[param_1] != (NetPlayer *)0x0)) {
    puVar1 = &netPlayerByTeam[param_1]->deaths;
    *puVar1 = *puVar1 + 1;
  }
  if (('\0' < param_2->killerTeam) && (netPlayerByTeam[param_2->killerTeam] != (NetPlayer *)0x0)) {
    puVar1 = &netPlayerByTeam[param_2->killerTeam]->kills;
    *puVar1 = *puVar1 + 1;
  }
  return;
}
