/*
 * Entry: 0054b689
 * Name: PromptSaveMission
 * Namespace: Global
 * Signature: int PromptSaveMission(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PromptSaveMission(void)

{
  char cVar1;
  bool bVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  MissionDialog local_268;
  char local_210 [40];
  undefined1 local_1e8 [220];
  char local_10c [260];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1e8;
  _getcwd(local_210,0x104);
  strncpy(local_10c,&loadFilename,0x104);
  pcVar3 = strrchr(local_10c,0x2e);
  iVar5 = 0;
  if (pcVar3 != (char *)0x0) {
    *pcVar3 = '\0';
  }
  MissionDialog::MissionDialog(&local_268);
  missionSave = true;
  bVar2 = MissionDialog::GetSaveName(&local_268,local_10c,true);
  if (bVar2) {
    _chdir(local_210);
    binarySave = BinarySave != 0;
    iVar5 = SaveGame(local_10c,0);
    binarySave = false;
    iVar4 = 0;
    do {
      cVar1 = local_10c[iVar4];
      (&loadFilename)[iVar4] = cVar1;
      iVar4 = iVar4 + 1;
    } while (cVar1 != '\0');
  }
  MissionDialog::~MissionDialog(&local_268);
  return iVar5;
}
