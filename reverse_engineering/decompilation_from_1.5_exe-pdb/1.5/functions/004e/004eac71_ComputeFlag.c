/*
 * Entry: 004eac71
 * Name: ComputeFlag
 * Namespace: Global
 * Signature: int ComputeFlag(tagENTITY * param_1, float param_2, uint param_3, uint param_4, uint param_5, uint param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
ComputeFlag(tagENTITY *param_1,float param_2,uint param_3,uint param_4,uint param_5,uint param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  
  fVar1 = (param_1->bSphere).radius;
  uVar5 = 0;
  if (((param_1->lodRangesSet < 1) || (10000.0 <= param_1->lodRanges[0])) ||
     (10000.0 <= param_1->lodRanges[1])) {
    fVar2 = (float)(int)LODInfo.textureRadius;
    if ((int)LODInfo.textureRadius < 0) {
      fVar2 = fVar2 + 4.2949673e+09;
    }
    fVar3 = (float)(int)LODInfo.fillRadius;
    if ((int)LODInfo.fillRadius < 0) {
      fVar3 = fVar3 + 4.2949673e+09;
    }
  }
  else {
    fVar2 = param_1->lodRanges[0];
    fVar3 = param_1->lodRanges[1];
  }
  if (fVar2 < fVar3) {
    fVar3 = fVar2;
  }
  if ((param_1->lodRangesSet < 1) || (10000.0 <= param_1->lodRanges[2])) {
    fVar4 = (float)(int)LODInfo.shadowRadius;
    if ((int)LODInfo.shadowRadius < 0) {
      fVar4 = fVar4 + 4.2949673e+09;
    }
  }
  else {
    fVar4 = param_1->lodRanges[2];
  }
  if (((fVar1 <= fVar3 * param_2) || (LODInfo.fillCount <= param_6)) ||
     (LODInfo.fillRange * LODInfo.fillRange < param_3 ||
      LODInfo.fillRange * LODInfo.fillRange - param_3 == 0)) {
    uVar5 = 0x2b;
  }
  if (((fVar1 <= fVar2 * param_2) || (LODInfo.textureCount <= param_5)) ||
     (LODInfo.textureRange * LODInfo.textureRange < param_3 ||
      LODInfo.textureRange * LODInfo.textureRange - param_3 == 0)) {
    uVar5 = uVar5 | 9;
  }
  fVar2 = (float)(int)LODInfo.lightRadius;
  if ((int)LODInfo.lightRadius < 0) {
    fVar2 = fVar2 + 4.2949673e+09;
  }
  if (((fVar1 <= fVar2 * param_2) || (LODInfo.lightCount <= param_4)) ||
     (LODInfo.lightRange * LODInfo.lightRange < param_3 ||
      LODInfo.lightRange * LODInfo.lightRange - param_3 == 0)) {
    uVar5 = uVar5 | 4;
  }
  fVar2 = (float)(int)LODInfo.bspRadius;
  if ((int)LODInfo.bspRadius < 0) {
    fVar2 = fVar2 + 4.2949673e+09;
  }
  if (((fVar1 <= fVar2 * param_2) || (LODInfo.bspCount <= param_4)) ||
     (LODInfo.bspRange * LODInfo.bspRange < param_3 ||
      LODInfo.bspRange * LODInfo.bspRange - param_3 == 0)) {
    uVar5 = uVar5 | 8;
  }
  fVar2 = (float)(int)LODInfo.lodRadius;
  if ((int)LODInfo.lodRadius < 0) {
    fVar2 = fVar2 + 4.2949673e+09;
  }
  if (((fVar1 <= fVar2 * param_2) || (LODInfo.lodCount <= param_4)) ||
     (LODInfo.lodRange * LODInfo.lodRange < param_3 ||
      LODInfo.lodRange * LODInfo.lodRange - param_3 == 0)) {
    uVar5 = uVar5 | 0x10;
  }
  if (((fVar1 <= fVar4 * param_2) || (LODInfo.shadowCount <= param_4)) ||
     (LODInfo.shadowRange * LODInfo.shadowRange < param_3 ||
      LODInfo.shadowRange * LODInfo.shadowRange - param_3 == 0)) {
    uVar5 = uVar5 | 0x20;
  }
  if (useD3D != 0) {
    uVar5 = uVar5 & 0xfffffffc;
  }
  return uVar5;
}
