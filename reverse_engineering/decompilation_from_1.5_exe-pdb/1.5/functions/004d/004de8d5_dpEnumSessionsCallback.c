/*
 * Entry: 004de8d5
 * Name: dpEnumSessionsCallback
 * Namespace: Global
 * Signature: int dpEnumSessionsCallback(dp_session_t * param_1, long * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl dpEnumSessionsCallback(dp_session_t *param_1,long *param_2,long param_3,void *param_4)

{
  byte bVar1;
  dp_session_t_u_23 *pdVar2;
  int iVar3;
  char *pcVar4;
  bool bVar5;
  
  if (param_1 == (dp_session_t *)0x0) {
    *(undefined4 *)param_4 = 3;
  }
  else {
    pcVar4 = Net::gameName;
    pdVar2 = &param_1->field8_0x17;
    do {
      bVar1 = pdVar2->sessionName[0];
      bVar5 = bVar1 < (byte)*pcVar4;
      if (bVar1 != *pcVar4) {
LAB_004de904:
        iVar3 = (1 - (uint)bVar5) - (uint)(bVar5 != 0);
        goto LAB_004de909;
      }
      if (bVar1 == 0) break;
      bVar1 = pdVar2->sessionName[1];
      bVar5 = bVar1 < (byte)pcVar4[1];
      if (bVar1 != pcVar4[1]) goto LAB_004de904;
      pdVar2 = (dp_session_t_u_23 *)((int)pdVar2 + 2);
      pcVar4 = pcVar4 + 2;
    } while (bVar1 != 0);
    iVar3 = 0;
LAB_004de909:
    if (iVar3 == 0) {
      Net::SetSession(param_4,param_1);
    }
  }
  return 0;
}
