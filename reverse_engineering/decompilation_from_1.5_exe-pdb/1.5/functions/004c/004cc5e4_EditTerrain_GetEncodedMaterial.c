/*
 * Entry: 004cc5e4
 * Name: EditTerrain::GetEncodedMaterial
 * Namespace: EditTerrain
 * Signature: ushort GetEncodedMaterial(EditTerrain * this, int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort __thiscall EditTerrain::GetEncodedMaterial(EditTerrain *this,int param_1,int param_2)

{
  ushort *puVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  ushort uVar7;
  uint uVar9;
  uint uVar10;
  short sVar8;
  
  puVar1 = GetTilePtr(param_1,param_2);
  uVar10 = (uint)(*puVar1 >> 0xc);
  puVar1 = GetTilePtr(param_1,param_2 + -2);
  uVar2 = (uint)(*puVar1 >> 0xc);
  puVar1 = GetTilePtr(param_1 + 2,param_2);
  uVar3 = (uint)(*puVar1 >> 0xc);
  puVar1 = GetTilePtr(param_1,param_2 + 2);
  uVar4 = (uint)(*puVar1 >> 0xc);
  puVar1 = GetTilePtr(param_1 + -2,param_2);
  uVar5 = (uint)(*puVar1 >> 0xc);
  uVar6 = uVar10;
  if (uVar2 < uVar10) {
    uVar6 = uVar2;
  }
  param_2 = uVar10;
  if (uVar10 < uVar2) {
    param_2 = uVar2;
  }
  if (uVar3 < uVar6) {
    uVar6 = uVar3;
  }
  if ((uint)param_2 < uVar3) {
    param_2 = uVar3;
  }
  if (uVar4 < uVar6) {
    uVar6 = uVar4;
  }
  if ((uint)param_2 < uVar4) {
    param_2 = uVar4;
  }
  if (uVar5 < uVar6) {
    uVar6 = uVar5;
  }
  if ((uint)param_2 < uVar5) {
    param_2 = uVar5;
  }
  param_1 = uVar6;
  if (uVar10 == uVar6) {
    param_1 = param_2;
  }
  uVar9 = (uint)(uVar10 != uVar2);
  if (uVar10 != uVar3) {
    uVar9 = uVar9 | 2;
  }
  if (uVar10 != uVar4) {
    uVar9 = uVar9 | 4;
  }
  if (uVar10 != uVar5) {
    uVar9 = uVar9 | 8;
  }
  if ((((((((uVar9 == 5) || (uVar9 == 7)) || (uVar9 == 10)) || ((uVar9 == 0xb || (uVar9 == 0xd))))
        || ((uVar9 == 0xe || (uVar9 == 0xf)))) || ((uVar10 != uVar6 && (uVar10 != param_2)))) ||
      ((uVar2 != uVar6 && (uVar2 != param_2)))) ||
     ((((uVar3 != uVar6 && (uVar3 != param_2)) || ((uVar4 != uVar6 && (uVar4 != param_2)))) ||
      ((uVar5 != uVar6 && (uVar5 != param_2)))))) {
    if (uVar10 != uVar6) {
      param_2 = uVar6;
    }
    uVar6 = param_2;
    uVar9 = 0;
    uVar10 = uVar6;
    param_2 = uVar6;
  }
  uVar3 = mix2cap[uVar9] | mix2rot[uVar9];
  uVar2 = rand();
  if (uVar6 == param_2) {
    uVar3 = (int)uVar2 >> 0xd;
  }
  uVar6 = uVar2 & 0xf;
  sVar8 = 0;
  uVar7 = 0;
  if (uVar6 < 8) {
    if (uVar6 < 4) {
      sVar8 = (uVar6 < 2) + 1;
    }
    uVar7 = sVar8 + 1;
  }
  return (ushort)(((param_1 | uVar10 << 4) << 4 | uVar3 & 0xf | uVar2 >> 2 & 4) << 4) | uVar7;
}
