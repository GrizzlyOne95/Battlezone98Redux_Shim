/*
 * Entry: 004dc6db
 * Name: Chat_DisplayMessage
 * Namespace: Global
 * Signature: void Chat_DisplayMessage(ushort param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Chat_DisplayMessage(ushort param_1,char *param_2)

{
  ushort uVar1;
  int iVar2;
  char *pcVar3;
  ulong uVar4;
  
  if (chat_display != (void *)0x0) {
    if (param_1 == 0) {
      if (system_on != 0) {
        Scroll_AddString(chat_display,param_2);
      }
    }
    else {
      iVar2 = Net_IsPlayerMuted(param_1);
      if (iVar2 == 0) {
        pcVar3 = NetPlayer_GetPlayerName(param_1);
        uVar4 = chat_color_broadcast;
        if ((((pcVar3 != (char *)0x0) &&
             (uVar1 = Net_GetMyPlayerID(), uVar4 = chat_color_self, param_1 != uVar1)) &&
            (iVar2 = NetPlayer_IsPlayerAlly(param_1), uVar4 = chat_color_ally, iVar2 == 0)) &&
           (iVar2 = NetPlayer_IsPlayerEnemy(param_1), uVar4 = chat_color_neutral, iVar2 != 0)) {
          uVar4 = chat_color_enemy;
        }
        Scroll_AddStringColored(chat_display,param_2,uVar4);
        return;
      }
    }
  }
  return;
}
