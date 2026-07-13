/*
 * Entry: 004c194c
 * Name: GetSpriteHeight
 * Namespace: Global
 * Signature: int GetSpriteHeight(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetSpriteHeight(int param_1)

{
  if ((-1 < param_1) && (param_1 < spriteTableSize)) {
    return spriteTable[param_1].height;
  }
  return spriteTable[0].height;
}
