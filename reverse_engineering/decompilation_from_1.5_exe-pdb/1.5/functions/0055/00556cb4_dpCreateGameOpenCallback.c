/*
 * Entry: 00556cb4
 * Name: dpCreateGameOpenCallback
 * Namespace: Global
 * Signature: int dpCreateGameOpenCallback(dp_session_t * param_1, long * param_2, long param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl dpCreateGameOpenCallback(dp_session_t *param_1,long *param_2,long param_3,void *param_4)

{
  uchar uVar1;
  uchar uVar2;
  uchar uVar3;
  int iVar4;
  char *pcVar5;
  dp_session_t *pdVar6;
  char *pcVar7;
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1 == (dp_session_t *)0x0) {
    pcVar5 = "Could not create game";
    pcVar7 = local_108;
    for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
      pcVar5 = pcVar5 + 4;
      pcVar7 = pcVar7 + 4;
    }
    *(undefined2 *)pcVar7 = *(undefined2 *)pcVar5;
    read_text_label("multi_error","cannot_create",local_108);
    do_error(param_4,local_108);
    bOpenFailed = true;
  }
  else {
    pdVar6 = &dp_session_game;
    for (iVar4 = 0x17; iVar4 != 0; iVar4 = iVar4 + -1) {
      uVar1 = param_1->adrMaster[0];
      uVar2 = param_1->adrMaster[1];
      uVar3 = param_1->adrMaster[2];
      pdVar6->field0_0x0 = param_1->field0_0x0;
      pdVar6->adrMaster[0] = uVar1;
      pdVar6->adrMaster[1] = uVar2;
      pdVar6->adrMaster[2] = uVar3;
      param_1 = (dp_session_t *)(param_1->adrMaster + 3);
      pdVar6 = (dp_session_t *)(pdVar6->adrMaster + 3);
    }
    uVar1 = param_1->adrMaster[0];
    pdVar6->field0_0x0 = param_1->field0_0x0;
    pdVar6->adrMaster[0] = uVar1;
    pdVar6->adrMaster[1] = param_1->adrMaster[1];
    createPlayer = true;
  }
  return 0;
}
