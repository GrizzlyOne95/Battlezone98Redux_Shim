/*
 * Entry: 00478d3d
 * Name: threadfunc
 * Namespace: Global
 * Signature: void threadfunc(void * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl threadfunc(void *param_1)

{
  int iVar1;
  
  do {
    if (net_stop != 0) goto LAB_00478d65;
    Sleep(100);
    iVar1 = Net_Execute();
  } while (iVar1 != 0);
  runningSS = 2;
LAB_00478d65:
  net_stopped = 1;
                    /* WARNING: Could not recover jumptable at 0x00478d6f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  _endthread();
  return;
}
