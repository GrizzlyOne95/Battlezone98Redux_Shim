/*
 * Entry: 00480c1f
 * Name: SetDS3DDefaults
 * Namespace: Global
 * Signature: void SetDS3DDefaults(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetDS3DDefaults(void)

{
  memset(&ds3dListener,0,0x40);
  memset(&ds3dBuffer,0,0x40);
  if (GM->listener != (IDirectSound3DListener *)0x0) {
    ds3dListener.flDistanceFactor = insideDistanceFactor;
    ds3dListener.dwSize = 0x40;
    ds3dBuffer.dwSize = 0x40;
    ds3dListener.flRolloffFactor = insideRolloffFactor;
    ds3dBuffer.dwInsideConeAngle = 0x168;
    ds3dBuffer.dwOutsideConeAngle = 0x168;
    ds3dListener.flDopplerFactor = insideDopplerFactor;
    ds3dBuffer.lConeOutsideVolume = 0;
    ds3dBuffer.dwMode = 0;
    ds3dBuffer.vConeOrientation.x = 0.0;
    ds3dBuffer.vConeOrientation.y = 0.0;
    ds3dBuffer.vConeOrientation.z = 1.0;
    ds3dBuffer.flMinDistance = 25.0;
    ds3dBuffer.flMaxDistance = 400.0;
  }
  return;
}
