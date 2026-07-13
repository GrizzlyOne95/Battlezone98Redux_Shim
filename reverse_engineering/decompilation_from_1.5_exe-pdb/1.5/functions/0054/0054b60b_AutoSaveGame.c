/*
 * Entry: 0054b60b
 * Name: AutoSaveGame
 * Namespace: Global
 * Signature: int AutoSaveGame(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl AutoSaveGame(void)

{
  int iVar1;
  char local_210 [260];
  char local_10c [260];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  _getcwd(local_210,0x104);
  binarySave = BinarySave != 0;
  builtin_strncpy(local_10c,"save\\autosave.sav",0x12);
  iVar1 = SaveGame(local_10c,1);
  binarySave = false;
  _chdir(local_210);
  return iVar1;
}
