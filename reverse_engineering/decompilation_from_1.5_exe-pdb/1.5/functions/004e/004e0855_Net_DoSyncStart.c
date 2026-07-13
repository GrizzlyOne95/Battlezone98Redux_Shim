/*
 * Entry: 004e0855
 * Name: Net_DoSyncStart
 * Namespace: Global
 * Signature: void Net_DoSyncStart(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_DoSyncStart(void)

{
  int iVar1;
  
  LoadPlayerData();
  if (Net::bSyncJoin != false) {
    theNet->bDoNetSync = true;
    sentsyncs = 0;
    do {
      if (theNet->bDoNetSync == false) break;
      iVar1 = Net::Execute(theNet);
    } while (iVar1 != 0);
    theNet->bDoNetSync = false;
  }
  return;
}
