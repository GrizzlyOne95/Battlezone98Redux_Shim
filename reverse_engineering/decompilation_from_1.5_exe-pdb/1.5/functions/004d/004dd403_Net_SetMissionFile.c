/*
 * Entry: 004dd403
 * Name: Net::SetMissionFile
 * Namespace: Net
 * Signature: void SetMissionFile(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net::SetMissionFile(char *param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (int)MissionFileName - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  return;
}
