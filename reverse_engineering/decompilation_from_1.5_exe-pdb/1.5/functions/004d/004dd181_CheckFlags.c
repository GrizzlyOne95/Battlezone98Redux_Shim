/*
 * Entry: 004dd181
 * Name: CheckFlags
 * Namespace: Global
 * Signature: void CheckFlags(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CheckFlags(void)

{
  int iVar1;
  
  reload_flags = 0;
  iVar1 = dpEnumPlayers(Net::dp,0,dpEnumPlayersCallbackFlags,0,0);
  if ((iVar1 == 0) && (reload_flags != 0)) {
    FlagDisplay::MakeTexture(&flagDisplay);
    return;
  }
  return;
}
