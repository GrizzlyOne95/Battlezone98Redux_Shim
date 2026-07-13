/*
 * Entry: 004c192c
 * Name: GetSpriteWidth
 * Namespace: Global
 * Signature: int GetSpriteWidth(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl GetSpriteWidth(int param_1)

{
  if ((-1 < param_1) && (param_1 < spriteTableSize)) {
    return spriteTable[param_1].width;
  }
  return spriteTable[0].width;
}
