/*
 * Entry: 004dd37a
 * Name: Net_SetSession
 * Namespace: Global
 * Signature: void Net_SetSession(dp_session_t * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Net_SetSession(dp_session_t *param_1)

{
  uchar uVar1;
  uchar uVar2;
  uchar uVar3;
  int iVar4;
  dp_session_t *pdVar5;
  
  Net::bFoundSession = true;
  pdVar5 = &Net::sDesc;
  for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1) {
    uVar1 = param_1->adrMaster[0];
    uVar2 = param_1->adrMaster[1];
    uVar3 = param_1->adrMaster[2];
    pdVar5->field0_0x0 = param_1->field0_0x0;
    pdVar5->adrMaster[0] = uVar1;
    pdVar5->adrMaster[1] = uVar2;
    pdVar5->adrMaster[2] = uVar3;
    param_1 = (dp_session_t *)(param_1->adrMaster + 3);
    pdVar5 = (dp_session_t *)(pdVar5->adrMaster + 3);
  }
  uVar1 = param_1->adrMaster[0];
  pdVar5->field0_0x0 = param_1->field0_0x0;
  pdVar5->adrMaster[0] = uVar1;
  pdVar5->adrMaster[1] = param_1->adrMaster[1];
  return;
}
