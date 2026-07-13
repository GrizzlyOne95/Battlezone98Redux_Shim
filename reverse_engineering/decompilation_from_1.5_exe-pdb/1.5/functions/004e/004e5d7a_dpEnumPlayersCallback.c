/*
 * Entry: 004e5d7a
 * Name: dpEnumPlayersCallback
 * Namespace: Global
 * Signature: void dpEnumPlayersCallback(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dpEnumPlayersCallback(ushort param_1,char *param_2,long param_3,void *param_4)

{
  ScorePlayer *this;
  
  if (param_1 != 0xfa01) {
    this = operator_new(0x88);
    if (this != (ScorePlayer *)0x0) {
      ScorePlayer::ScorePlayer(this,param_1);
    }
  }
  return;
}
