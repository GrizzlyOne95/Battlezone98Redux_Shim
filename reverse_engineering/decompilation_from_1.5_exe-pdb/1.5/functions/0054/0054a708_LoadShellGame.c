/*
 * Entry: 0054a708
 * Name: LoadShellGame
 * Namespace: Global
 * Signature: int LoadShellGame(_iobuf * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl LoadShellGame(_iobuf *param_1,int param_2)

{
  in(param_1,&nUsaMissionIndex,4);
  in(param_1,&nUssrMissionIndex,4);
  in(param_1,&nTrnMissionIndex,4);
  in(param_1,&nPlayerSide,4);
  in(param_1,&nMissionStatus,4);
  if (0x40a < version) {
    in(param_1,&nOldMissionMode,4);
  }
  if (param_2 == 1) {
    SetRunning(2);
  }
  return 1;
}
