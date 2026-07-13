/*
 * Entry: 0054a5a4
 * Name: PromptLoadGame
 * Namespace: Global
 * Signature: int PromptLoadGame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PromptLoadGame(void)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  MissionDialog local_164;
  char local_10c [40];
  undefined1 local_e4 [220];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_e4;
  strncpy(local_10c,&loadFilename,0x104);
  MissionDialog::MissionDialog(&local_164);
  bVar2 = MissionDialog::GetLoadName(&local_164,local_10c,false);
  iVar4 = 0;
  if (bVar2) {
    doload = 0;
    iVar4 = 1;
    saveload = 1;
    iVar3 = 0;
    do {
      cVar1 = local_10c[iVar3];
      (&loadFilename)[iVar3] = cVar1;
      iVar3 = iVar3 + 1;
    } while (cVar1 != '\0');
    SetRunning(9);
  }
  MissionDialog::~MissionDialog(&local_164);
  return iVar4;
}
