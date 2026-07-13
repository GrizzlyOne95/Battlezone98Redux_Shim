/*
 * Entry: 004de6f3
 * Name: Net::HandleGameInfoData
 * Namespace: Net
 * Signature: void HandleGameInfoData(dp_s * param_1, ushort param_2, uint param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net::HandleGameInfoData(dp_s *param_1,ushort param_2,uint param_3,void *param_4)

{
  TimeLimit = *(int *)param_4;
  KillLimit = *(int *)((int)param_4 + 4);
  FlagLimit = *(int *)((int)param_4 + 8);
  if (iStartLivesLeft != *(int *)((int)param_4 + 0xc)) {
    iLivesLeft = *(int *)((int)param_4 + 0xc);
  }
  iStartLivesLeft = *(int *)((int)param_4 + 0xc);
  if (iLivesLeft == -1) {
    iLivesLeft = *(int *)((int)param_4 + 0xc);
  }
  bSniper = (bool)*(undefined1 *)((int)param_4 + 0x10);
  bNations = (bool)*(undefined1 *)((int)param_4 + 0x11);
  return;
}
