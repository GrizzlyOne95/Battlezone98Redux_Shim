/*
 * Entry: 00480cc7
 * Name: SetGASVolumeLevels
 * Namespace: Global
 * Signature: void SetGASVolumeLevels(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetGASVolumeLevels(void)

{
  int iVar1;
  int extraout_EAX;
  int local_8;
  
  VolumeLevels[0] = -10000;
  local_8 = 1;
  do {
    _ftol2_sse();
    iVar1 = local_8 + 1;
    VolumeLevels[local_8] = extraout_EAX << 2;
    local_8 = iVar1;
  } while (iVar1 < 0x65);
  return;
}
