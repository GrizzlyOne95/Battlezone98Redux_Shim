/*
 * Entry: 004dd984
 * Name: Net_CreatePlayer
 * Namespace: Global
 * Signature: void Net_CreatePlayer(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_CreatePlayer(int param_1)

{
  AiMission *pAVar1;
  
  pAVar1 = AiMission::GetCurrent();
                    /* WARNING: Could not recover jumptable at 0x004dd98d. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(pAVar1->_padding_ + 0x34))();
  return;
}
