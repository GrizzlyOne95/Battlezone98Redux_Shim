/*
 * Entry: 0054b55d
 * Name: PromptSaveGame
 * Namespace: Global
 * Signature: int PromptSaveGame(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PromptSaveGame(int param_1)

{
  bool bVar1;
  int iVar2;
  MissionDialog local_268;
  char local_210 [40];
  undefined1 local_1e8 [220];
  char local_10c [260];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1e8;
  _getcwd(local_210,0x104);
  iVar2 = 0;
  local_10c[0] = '\0';
  MissionDialog::MissionDialog(&local_268);
  missionSave = false;
  bVar1 = MissionDialog::GetSaveName(&local_268,local_10c,false);
  if (bVar1) {
    _chdir(local_210);
    binarySave = BinarySave != 0;
    iVar2 = SaveGame(local_10c,param_1);
    binarySave = false;
  }
  MissionDialog::~MissionDialog(&local_268);
  return iVar2;
}
