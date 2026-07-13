/*
 * Entry: 004cc786
 * Name: EditTerrain::Copy
 * Namespace: EditTerrain
 * Signature: void Copy(EditTerrain * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::Copy(EditTerrain *this,VECTOR_3D *param_1)

{
  ushort *puVar1;
  short (*pasVar2) [64];
  int iVar3;
  short *psVar4;
  VECTOR_3D *pVVar5;
  short (*pasVar6) [64];
  short sVar7;
  int iVar8;
  undefined4 uVar9;
  FLOAT2INT local_20;
  FLOAT2INT local_18;
  short (*local_10) [64];
  int local_c;
  int local_8;
  
  if (TerrainWireFrame != 0) {
    WorldToGrid(this,&local_20,&local_18,param_1);
    pVVar5 = (VECTOR_3D *)(local_20.i - this->brushWidth / 2);
    local_c = (int)&pVVar5->x + this->brushWidth;
    iVar8 = local_18.i - this->brushDepth / 2;
    local_20._4_4_ = this->brushDepth + iVar8;
    if (iVar8 <= (int)local_20._4_4_) {
      local_18._4_4_ = this->copyGrid;
      local_8 = iVar8;
      do {
        if ((int)pVVar5 <= local_c) {
          local_10 = (short (*) [64])local_18._4_4_;
          param_1 = pVVar5;
          do {
            puVar1 = GetZonePtr((int)param_1,local_8);
            param_1 = (VECTOR_3D *)((int)&param_1->x + 1);
            psVar4 = *local_10;
            (*local_10)[0] = *puVar1 & 0xfff;
            local_10 = (short (*) [64])(psVar4 + 1);
          } while ((int)param_1 <= local_c);
        }
        local_8 = local_8 + 1;
        local_18._4_4_ = local_18._4_4_ + 0x80;
      } while (local_8 <= (int)local_20._4_4_);
    }
    if (iVar8 <= (int)local_20._4_4_) {
      local_18._4_4_ = this->copyTile;
      local_8 = iVar8;
      do {
        uVar9 = local_18._4_4_;
        param_1 = pVVar5;
        if ((int)pVVar5 <= local_c) {
          do {
            puVar1 = GetTilePtr((int)param_1,local_8);
            param_1 = (VECTOR_3D *)((int)&param_1->x + 1);
            (*(short (*) [64])uVar9)[0] = *puVar1;
            uVar9 = (short (*) [64])(*(short (*) [64])uVar9 + 1);
          } while ((int)param_1 <= local_c);
        }
        local_8 = local_8 + 1;
        local_18._4_4_ = local_18._4_4_ + 0x80;
      } while (local_8 <= (int)local_20._4_4_);
    }
    pasVar6 = this->copyGrid;
    sVar7 = (*pasVar6)[0];
    if (-1 < this->brushDepth) {
      psVar4 = this->copyGrid[0] + this->brushWidth;
      iVar8 = this->brushDepth + 1;
      do {
        if ((*pasVar6)[0] < sVar7) {
          sVar7 = (*pasVar6)[0];
        }
        if (*psVar4 < sVar7) {
          sVar7 = *psVar4;
        }
        pasVar6 = pasVar6 + 1;
        psVar4 = psVar4 + 0x40;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    if (-1 < this->brushWidth) {
      pasVar6 = this->copyGrid;
      pasVar2 = this->copyGrid + this->brushDepth;
      iVar8 = this->brushWidth + 1;
      do {
        if ((*pasVar6)[0] < sVar7) {
          sVar7 = (*pasVar6)[0];
        }
        if ((*pasVar2)[0] < sVar7) {
          sVar7 = (*pasVar2)[0];
        }
        pasVar6 = (short (*) [64])(*pasVar6 + 1);
        pasVar2 = (short (*) [64])(*pasVar2 + 1);
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    iVar8 = 0;
    if (-1 < this->brushDepth) {
      pasVar6 = this->copyGrid;
      do {
        iVar3 = 0;
        pasVar2 = pasVar6;
        if (-1 < this->brushWidth) {
          do {
            (*pasVar2)[0] = (*pasVar2)[0] - sVar7;
            iVar3 = iVar3 + 1;
            pasVar2 = (short (*) [64])(*pasVar2 + 1);
          } while (iVar3 <= this->brushWidth);
        }
        iVar8 = iVar8 + 1;
        pasVar6 = pasVar6 + 1;
      } while (iVar8 <= this->brushDepth);
    }
    this->copyWidth = this->brushWidth;
    this->copyDepth = this->brushDepth;
  }
  return;
}
