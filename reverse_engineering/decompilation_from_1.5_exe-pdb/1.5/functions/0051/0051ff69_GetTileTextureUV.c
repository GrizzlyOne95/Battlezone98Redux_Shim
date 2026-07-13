/*
 * Entry: 0051ff69
 * Name: GetTileTextureUV
 * Namespace: Global
 * Signature: TEXTURE * GetTileTextureUV(long param_1, long param_2, float * param_3, float * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TEXTURE * __cdecl GetTileTextureUV(long param_1,long param_2,float *param_3,float *param_4)

{
  byte bVar1;
  ushort uVar2;
  ushort *puVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  puVar3 = GetTilePtr(param_1,param_2);
  uVar2 = *puVar3;
  uVar4 = uVar2 >> 4 & 0xf;
  uVar5 = param_2 & 1;
  uVar6 = param_1 & 1;
  bVar1 = TileIndex[uVar2 >> 0xc][uVar2 >> 8 & 0xf][uVar2 & 3][uVar2 >> 7 & 1];
  *param_3 = mix2UV[uVar4][uVar5][uVar6].u0;
  *param_4 = mix2UV[uVar4][uVar5][uVar6].v0;
  param_3[1] = mix2UV[uVar4][uVar5][uVar6].u1;
  param_4[1] = mix2UV[uVar4][uVar5][uVar6].v1;
  param_3[2] = mix2UV[uVar4][uVar5][uVar6].u2;
  param_4[2] = mix2UV[uVar4][uVar5][uVar6].v2;
  param_3[3] = mix2UV[uVar4][uVar5][uVar6].u3;
  param_4[3] = mix2UV[uVar4][uVar5][uVar6].v3;
  return (TEXTURE *)(&DAT_00caf4ec)[bVar1];
}
