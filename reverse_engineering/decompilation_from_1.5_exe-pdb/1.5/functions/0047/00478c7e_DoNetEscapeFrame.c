/*
 * Entry: 00478c7e
 * Name: DoNetEscapeFrame
 * Namespace: Global
 * Signature: void DoNetEscapeFrame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DoNetEscapeFrame(void)

{
  int iVar1;
  bool bVar2;
  float fVar3;
  
  bVar2 = runningSS == 5;
  if (bVar2) {
    iVar1 = Net_IsNetGame();
    if ((((iVar1 != 0) && (iVar1 = Net_IsDeathMatch(), iVar1 == 0)) && (respawn == 1)) &&
       (fVar3 = Get_TimeLocal(), respawn_timer < fVar3)) {
      respawn = 0;
      Net_CreatePlayer(0);
      if (runningSS != 5) {
        return;
      }
    }
    SetLoopTimes();
    iVar1 = UserPref_arcadeMode();
    if (iVar1 == 0) {
      CheckEntityCollisions();
    }
    GameFeature_ControlAll();
  }
  iVar1 = Net_Execute();
  if (iVar1 == 0) {
    runningSS = 2;
  }
  if (!bVar2) {
    return;
  }
  iVar1 = UserPref_arcadeMode();
  if (iVar1 == 0) {
    Manage_AI(&Device);
  }
  Simulate();
  ControlWeapons();
  GameObject_BroadCast();
  TexAnim_Animate();
  NextGAS(1);
  Init_Object_Database();
  return;
}
