/*
 * Entry: 004dd8fe
 * Name: Net_SetODF
 * Namespace: Global
 * Signature: void Net_SetODF(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetODF(char *param_1)

{
  strncpy(Net::odfName,param_1,6);
  return;
}
