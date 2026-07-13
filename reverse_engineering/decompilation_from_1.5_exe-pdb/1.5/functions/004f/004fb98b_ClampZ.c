/*
 * Entry: 004fb98b
 * Name: ClampZ
 * Namespace: Global
 * Signature: void ClampZ(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ClampZ(void)

{
  if (spriteZ < 0.1) {
    spriteZ = 0.1;
  }
  if (spriteZ <= 1640.0) {
    return;
  }
  spriteZ = 1640.0;
  return;
}
