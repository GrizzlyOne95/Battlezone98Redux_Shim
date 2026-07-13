/*
 * Entry: 004d9f78
 * Name: GetSpriteTextureUV
 * Namespace: Global
 * Signature: TEXTURE * GetSpriteTextureUV(int param_1, float * param_2, float * param_3, float * param_4, float * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl
GetSpriteTextureUV(int param_1,float *param_2,float *param_3,float *param_4,float *param_5)

{
  TEXTURE *pTVar1;
  float fVar2;
  float fVar3;
  
  if ((param_1 < 0) || (spriteTableSize <= param_1)) {
    param_1 = 0;
  }
  pTVar1 = spriteTable[param_1].texPtr;
  fVar2 = 1.0 / (float)(int)(pTVar1->width >> (2 < pTVar1->type) + (0 < pTVar1->type));
  fVar3 = 1.0 / (float)pTVar1->height;
  if (param_2 != (float *)0x0) {
    *param_2 = (float)spriteTable[param_1].u * fVar2;
  }
  if (param_3 != (float *)0x0) {
    *param_3 = (float)spriteTable[param_1].v * fVar3;
  }
  if (param_4 != (float *)0x0) {
    *param_4 = (float)(spriteTable[param_1].width + spriteTable[param_1].u) * fVar2;
  }
  if (param_5 != (float *)0x0) {
    *param_5 = fVar3 * (float)(spriteTable[param_1].height + spriteTable[param_1].v);
  }
  return pTVar1;
}
