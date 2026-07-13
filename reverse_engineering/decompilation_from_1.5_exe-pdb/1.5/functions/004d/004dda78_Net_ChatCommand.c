/*
 * Entry: 004dda78
 * Name: Net_ChatCommand
 * Namespace: Global
 * Signature: int Net_ChatCommand(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Net_ChatCommand(char *param_1)

{
  AiMission *pAVar1;
  uint uVar2;
  
  pAVar1 = AiMission::GetCurrent();
  if (pAVar1 != (AiMission *)0x0) {
    uVar2 = (**(code **)(pAVar1->_padding_ + 0x40))(param_1);
    return uVar2 & 0xff;
  }
  return 0;
}
