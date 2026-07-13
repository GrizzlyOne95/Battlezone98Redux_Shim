/*
 * Entry: 0055aaca
 * Name: whisper_packet_id_callback
 * Namespace: Global
 * Signature: void whisper_packet_id_callback(ushort param_1, char * param_2, char * param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl whisper_packet_id_callback(ushort param_1,char *param_2,char *param_3,uint param_4)

{
  bool bVar1;
  
  bVar1 = PlayerList::IsMuted((PlayerList *)&playersInSyncGame,param_1);
  if (!bVar1) {
    Chat::AppendWhisper((Chat *)&chatGame,param_2,param_4,param_3);
  }
  return;
}
