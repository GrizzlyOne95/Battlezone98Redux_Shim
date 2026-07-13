/*
 * Entry: 00481ee5
 * Name: StopGAS
 * Namespace: Global
 * Signature: int StopGAS(GAS_MASTER * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl StopGAS(GAS_MASTER *param_1)

{
  int *piVar1;
  int *in_EAX;
  int iVar2;
  
  StopActiveList();
  piVar1 = (int *)in_EAX[1];
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 0x48))(piVar1);
    piVar1 = (int *)in_EAX[2];
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 8))(piVar1);
    }
    (**(code **)(*(int *)in_EAX[1] + 8))((int *)in_EAX[1]);
    in_EAX[1] = 0;
    in_EAX[2] = 0;
  }
  piVar1 = (int *)*in_EAX;
  if (piVar1 != (int *)0x0) {
    (**(code **)(*piVar1 + 8))(piVar1);
    *in_EAX = 0;
  }
  for (iVar2 = 9; iVar2 != 0; iVar2 = iVar2 + -1) {
    *in_EAX = 0;
    in_EAX = in_EAX + 1;
  }
  OggManager::Cleanup();
  return 1;
}
