/*
 * Entry: 004ddf34
 * Name: Net_SetParams
 * Namespace: Global
 * Signature: void Net_SetParams(commInitReq_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetParams(commInitReq_t *param_1)

{
  int iVar1;
  commInitReq_t *pcVar2;
  
  pcVar2 = &Net::params;
  for (iVar1 = 0xb; iVar1 != 0; iVar1 = iVar1 + -1) {
    pcVar2->reqLen = param_1->reqLen;
    param_1 = (commInitReq_t *)&param_1->sessionId;
    pcVar2 = (commInitReq_t *)&pcVar2->sessionId;
  }
  return;
}
