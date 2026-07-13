/*
 * Entry: 0044c7b0
 * Name: MyMessageHandler
 * Namespace: Global
 * Signature: int MyMessageHandler(ushort param_1, char * param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl MyMessageHandler(ushort param_1,char *param_2,int param_3)

{
  if ((*param_2 == '#') && (param_2[1] == 'R')) {
    MultGMission::multGEvent->reset = 1;
    return 1;
  }
  return 0;
}
