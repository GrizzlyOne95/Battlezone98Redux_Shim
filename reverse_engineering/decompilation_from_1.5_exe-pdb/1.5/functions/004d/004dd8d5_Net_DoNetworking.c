/*
 * Entry: 004dd8d5
 * Name: Net_DoNetworking
 * Namespace: Global
 * Signature: void Net_DoNetworking(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_DoNetworking(int param_1)

{
  Net::runNetworking = param_1 != 0;
  return;
}
