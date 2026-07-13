/*
 * Entry: 0054b76e
 * Name: CheckResaveMission
 * Namespace: Global
 * Signature: int CheckResaveMission(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckResaveMission(void)

{
  int iVar1;
  
  if ((Resave != 0) && (version < 0x415)) {
    iVar1 = PromptSaveMission();
    return iVar1;
  }
  return 0;
}
