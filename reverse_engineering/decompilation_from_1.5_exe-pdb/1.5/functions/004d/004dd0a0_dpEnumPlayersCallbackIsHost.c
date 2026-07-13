/*
 * Entry: 004dd0a0
 * Name: dpEnumPlayersCallbackIsHost
 * Namespace: Global
 * Signature: void dpEnumPlayersCallbackIsHost(ushort param_1, char * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl dpEnumPlayersCallbackIsHost(ushort param_1,char *param_2,long param_3,void *param_4)

{
  if (param_1 < *(ushort *)param_4) {
    *(ushort *)param_4 = param_1;
  }
  if (param_1 == 0xfa01) {
    done = 1;
  }
  return;
}
