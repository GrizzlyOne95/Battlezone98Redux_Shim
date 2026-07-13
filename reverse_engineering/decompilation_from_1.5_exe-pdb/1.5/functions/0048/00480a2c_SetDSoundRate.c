/*
 * Entry: 00480a2c
 * Name: SetDSoundRate
 * Namespace: Global
 * Signature: int SetDSoundRate(GAS_MASTER * param_1, ulong param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl SetDSoundRate(GAS_MASTER *param_1,ulong param_2)

{
  int iVar1;
  undefined4 local_14;
  ulong local_10;
  int local_c;
  undefined4 local_8;
  
  if ((param_1 != (GAS_MASTER *)0x0) && (param_1->primaryBuffer != (IDirectSoundBuffer *)0x0)) {
    local_14 = 0x20001;
    local_c = param_2 << 2;
    local_8 = 0x100004;
    local_10 = param_2;
    iVar1 = (**(code **)((int)*param_1->primaryBuffer + 0x38))(param_1->primaryBuffer,&local_14);
    if (iVar1 != 0) {
      DEBUG_systemWarning("Can\'t set DSound primary buffer rate to %d.");
      return 0;
    }
  }
  return 1;
}
