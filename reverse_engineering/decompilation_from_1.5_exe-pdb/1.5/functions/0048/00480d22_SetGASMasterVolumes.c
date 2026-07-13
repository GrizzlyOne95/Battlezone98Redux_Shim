/*
 * Entry: 00480d22
 * Name: SetGASMasterVolumes
 * Namespace: Global
 * Signature: void SetGASMasterVolumes(long param_1, long param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetGASMasterVolumes(long param_1,long param_2,long param_3)

{
  if (param_1 == -1) {
    param_1 = (long)(UserProfilePtr->audioControl).music;
  }
  if (param_2 == -1) {
    param_2 = (long)(UserProfilePtr->audioControl).sfx;
  }
  if (param_3 == -1) {
    param_3 = (long)(UserProfilePtr->audioControl).voice;
  }
  if (param_1 != 0xfffffffe) {
    SetMusicVolume(param_1);
  }
  if (GM != (GAS_MASTER *)0x0) {
    if (param_2 != 0xfffffffe) {
      GM->masterVolume1 = param_2;
    }
    if (param_3 != 0xfffffffe) {
      GM->masterVolume2 = param_3;
    }
  }
  return;
}
