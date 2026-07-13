/*
 * Entry: 004be141
 * Name: BettyVoiceDone
 * Namespace: Global
 * Signature: int BettyVoiceDone(_gas_object * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BettyVoiceDone(_gas_object *param_1,long param_2)

{
  StopGASEvent(param_1);
  voiceReady = true;
  return 0;
}
