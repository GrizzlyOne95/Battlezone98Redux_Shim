/*
 * Entry: 0054a639
 * Name: SaveShellGame
 * Namespace: Global
 * Signature: int SaveShellGame(_iobuf * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SaveShellGame(_iobuf *param_1,int param_2)

{
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = nUsaMissionIndex;
  local_c = nUssrMissionIndex;
  local_10 = nTrnMissionIndex;
  if (((nMissionStatus == 2) && (param_2 == 1)) && (nOldMissionMode == 0)) {
    if (nPlayerSide == 1) {
      local_8 = nUsaMissionIndex + 1;
    }
    else if (nPlayerSide == 2) {
      local_c = nUssrMissionIndex + 1;
    }
    else if (nPlayerSide == 3) {
      local_10 = nTrnMissionIndex + 1;
    }
  }
  out(param_1,&local_8,4,"nUsaMissionIndex");
  out(param_1,&local_c,4,"nUssrMissionIndex");
  out(param_1,&local_10,4,"nTrnMissionIndex");
  out(param_1,&nPlayerSide,4,"nPlayerSide");
  out(param_1,&nMissionStatus,4,"nMissionStatus");
  out(param_1,&nOldMissionMode,4,"nOldMissionMode");
  return 1;
}
