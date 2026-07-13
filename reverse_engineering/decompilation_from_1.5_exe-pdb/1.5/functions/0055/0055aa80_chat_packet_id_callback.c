/*
 * Entry: 0055aa80
 * Name: chat_packet_id_callback
 * Namespace: Global
 * Signature: void chat_packet_id_callback(ushort param_1, char * param_2, char * param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl chat_packet_id_callback(ushort param_1,char *param_2,char *param_3,uint param_4)

{
  bool bVar1;
  Chat *in_ECX;
  
  if (param_1 == 0) {
    Chat::Append(in_ECX,(char *)&chatGame);
    return;
  }
  bVar1 = PlayerList::IsMuted((PlayerList *)&playersInSyncGame,param_1);
  if (!bVar1) {
    Chat::AppendMessage((Chat *)&chatGame,param_2,param_4,param_3);
  }
  return;
}
