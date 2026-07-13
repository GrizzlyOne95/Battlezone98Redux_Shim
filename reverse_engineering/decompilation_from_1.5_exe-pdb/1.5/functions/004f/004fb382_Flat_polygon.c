/*
 * Entry: 004fb382
 * Name: Flat_polygon
 * Namespace: Global
 * Signature: void Flat_polygon(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
Flat_polygon(_GRAPHIC_BUFFER *param_1,POINT_3D *param_2,long param_3,POLYGON_SKIN param_4)

{
  float fVar1;
  float fVar2;
  uchar uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  uint uVar7;
  int in_EDX;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uchar *puVar11;
  uchar *local_694;
  uint local_688;
  int local_680 [6];
  int aiStack_668 [180];
  int aiStack_398 [6];
  int aiStack_380 [192];
  int local_80;
  int local_7c;
  float local_78;
  float local_74;
  int local_70;
  int local_6c;
  float local_68;
  float local_64;
  double local_50;
  double local_48;
  double local_40;
  
  fVar1 = (param_2->Texel).field2_0x8.luma;
  iVar5 = 10000;
  iVar4 = 0;
  do {
    local_680[0] = iVar4;
    fVar2 = *(float *)((int)&(param_2->Vector).y + local_680[0]);
    *(int *)((int)aiStack_398 + local_680[0]) = local_680[0];
    *(int *)((int)aiStack_668 + local_680[0]) = local_680[0];
    local_50 = (double)(fVar2 + (float)Float2Int);
    if (local_50._0_4_ <= iVar5) {
      iVar5 = local_50._0_4_;
      in_EDX = local_680[0];
    }
    *(int *)((int)aiStack_380 + local_680[0] + 4) = local_50._0_4_;
    param_3 = param_3 + -1;
    iVar4 = local_680[0] + 0x18;
  } while (param_3 != 0);
  *(undefined4 *)((int)aiStack_380 + local_680[0]) = 0;
  local_688 = SUB84((double)((UNITY - fVar1) * LUM_SCALE + (float)Float2Int),0);
  uVar3 = Luminance_Table[0][(local_688 & 0xff00) + (param_4.Color & 0xffU)];
  local_70 = in_EDX;
  local_80 = in_EDX;
  local_6c = in_EDX;
  uVar6 = CONCAT22(CONCAT11(uVar3,uVar3),CONCAT11(uVar3,uVar3));
  local_7c = in_EDX;
  iVar4 = param_1->Width;
  local_694 = param_1->Buffer + (param_1->Pane).x0 + (iVar5 + (param_1->Pane).y0) * iVar4;
  iVar5 = *(int *)((int)aiStack_380 + in_EDX + 4);
  do {
    if (*(int *)((int)aiStack_380 + local_6c + 4) <= iVar5) {
      do {
        iVar8 = local_6c;
        local_6c = *(int *)((int)aiStack_380 + iVar8);
        if (local_6c == in_EDX) {
          return;
        }
      } while (*(int *)((int)aiStack_380 + local_6c + 4) <= iVar5);
      local_50 = (double)(*(float *)((int)&(param_2->Vector).y + iVar8) + (float)Float2Int);
      local_64 = (*(float *)((int)&(param_2->Vector).x + local_6c) -
                 *(float *)((int)&(param_2->Vector).x + iVar8)) *
                 (UNITY / (*(float *)((int)&(param_2->Vector).y + local_6c) -
                          *(float *)((int)&(param_2->Vector).y + iVar8)));
      local_68 = ((float)local_50._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar8)) * local_64
                 + *(float *)((int)&(param_2->Vector).x + iVar8);
    }
    if (*(int *)((int)aiStack_380 + local_7c + 4) <= iVar5) {
      do {
        iVar8 = local_7c;
        local_7c = *(int *)((int)local_680 + iVar8);
      } while (*(int *)((int)aiStack_380 + local_7c + 4) <= iVar5);
      local_50 = (double)(*(float *)((int)&(param_2->Vector).y + iVar8) + (float)Float2Int);
      local_74 = (*(float *)((int)&(param_2->Vector).x + local_7c) -
                 *(float *)((int)&(param_2->Vector).x + iVar8)) *
                 (UNITY / (*(float *)((int)&(param_2->Vector).y + local_7c) -
                          *(float *)((int)&(param_2->Vector).y + iVar8)));
      local_78 = ((float)local_50._0_4_ - *(float *)((int)&(param_2->Vector).y + iVar8)) * local_74
                 + *(float *)((int)&(param_2->Vector).x + iVar8);
    }
    local_40 = (double)(local_68 + (float)Float2Int);
    local_48 = (double)(local_78 + (float)Float2Int);
    local_40._0_4_ = SUB84((double)(local_68 + (float)Float2Int),0);
    local_48._0_4_ = SUB84((double)(local_78 + (float)Float2Int),0);
    if (local_48._0_4_ != local_40._0_4_) {
      iVar8 = local_40._0_4_;
      if (local_48._0_4_ < local_40._0_4_) {
        iVar8 = local_48._0_4_;
        local_48._0_4_ = local_40._0_4_;
      }
      uVar9 = local_48._0_4_ - iVar8;
      puVar11 = local_694 + iVar8;
      if (0x1e < (int)uVar9) {
        uVar7 = -(int)puVar11 & 0x1f;
        uVar10 = uVar9 - uVar7;
        for (; uVar7 != 0; uVar7 = uVar7 - 1) {
          *puVar11 = uVar3;
          puVar11 = puVar11 + 1;
        }
        uVar9 = uVar10 & 0x1f;
        for (; 0x1f < (int)uVar10; uVar10 = uVar10 - 0x20) {
          *(undefined4 *)puVar11 = uVar6;
          *(undefined4 *)(puVar11 + 0x10) = uVar6;
          *(undefined4 *)(puVar11 + 4) = uVar6;
          *(undefined4 *)(puVar11 + 0x14) = uVar6;
          *(undefined4 *)(puVar11 + 8) = uVar6;
          *(undefined4 *)(puVar11 + 0x18) = uVar6;
          *(undefined4 *)(puVar11 + 0xc) = uVar6;
          *(undefined4 *)(puVar11 + 0x1c) = uVar6;
          puVar11 = puVar11 + 0x20;
        }
      }
      for (; uVar9 != 0; uVar9 = uVar9 - 1) {
        *puVar11 = uVar3;
        puVar11 = puVar11 + 1;
      }
    }
    local_694 = local_694 + iVar4;
    iVar5 = iVar5 + 1;
    local_68 = local_68 + local_64;
    local_78 = local_78 + local_74;
  } while( true );
}
