/*
 * Entry: 004cac59
 * Name: EditTerrain::DrawMenu
 * Namespace: EditTerrain
 * Signature: void DrawMenu(EditTerrain * this, tagIconMenu * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::DrawMenu(EditTerrain *this,tagIconMenu *param_1)

{
  tagRECT *ptVar1;
  tagIcon *ptVar2;
  long lVar3;
  long lVar4;
  long lVar5;
  long lVar6;
  tagPOINT tVar7;
  float fVar8;
  int iVar9;
  int iVar10;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  
  fVar8 = spriteZ;
  spriteZ = spriteZ + 0.3;
  iVar10 = param_1->icons / 2;
  Clipped_Rect_Filled(DisplayInterface::currentBuffer,(param_1->rect).left + -1,
                      (param_1->rect).top + -1,(param_1->rect).right + 1,(param_1->rect).bottom + 1,
                      this->colorBLACK,SOLID_PIXELS);
  local_18 = 0;
  local_20 = 2;
  do {
    if (0 < iVar10) {
      local_14 = local_18;
      local_1c = iVar10;
      do {
        ptVar2 = param_1->icon;
        ptVar1 = (tagRECT *)((int)&(ptVar2->rect).left + local_14);
        spriteZ = fVar8 + 0.2;
        Clipped_Rect_Filled(DisplayInterface::currentBuffer,ptVar1->left,
                            *(long *)((int)&(ptVar2->rect).top + local_14),
                            *(long *)((int)&(ptVar2->rect).right + local_14),
                            *(long *)((int)&(ptVar2->rect).bottom + local_14),this->colorLTGREY,
                            SOLID_PIXELS);
        tVar7.y = DisplayInterface::mousePos.y;
        tVar7.x = DisplayInterface::mousePos.x;
        spriteZ = fVar8 + 0.1;
        iVar9 = InsideRect(tVar7,ptVar1);
        if ((iVar9 == 0) || (edit_controls.edit_lmouse == '\0')) {
          DrawSprite(DisplayInterface::currentBuffer,*(int *)((int)&ptVar2->index + local_14),
                     ptVar1->left + 4,*(int *)((int)&(ptVar2->rect).top + local_14) + 4,1);
          lVar3 = *(long *)((int)&(ptVar2->rect).top + local_14);
          lVar4 = *(long *)((int)&(ptVar2->rect).right + local_14);
          lVar5 = *(long *)((int)&(ptVar2->rect).bottom + local_14);
          lVar6 = ptVar1->left;
          Graphic_Line(DisplayInterface::currentBuffer,lVar6,lVar3,lVar6,lVar5,this->colorWHITE,
                       SOLID_PIXELS);
          Graphic_Line(DisplayInterface::currentBuffer,lVar6,lVar3,lVar4,lVar3,this->colorWHITE,
                       SOLID_PIXELS);
          Graphic_Line(DisplayInterface::currentBuffer,lVar4,lVar5,lVar6,lVar5,this->colorDKGREY,
                       SOLID_PIXELS);
          Graphic_Line(DisplayInterface::currentBuffer,lVar4,lVar5,lVar4,lVar3,this->colorDKGREY,
                       SOLID_PIXELS);
        }
        else {
          DrawSprite(DisplayInterface::currentBuffer,*(int *)((int)&ptVar2->index + local_14),
                     ptVar1->left + 6,*(int *)((int)&(ptVar2->rect).top + local_14) + 6,1);
        }
        local_14 = local_14 + 0x24;
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
    local_18 = local_18 + iVar10 * 0x24;
    local_20 = local_20 + -1;
  } while (local_20 != 0);
  spriteZ = fVar8;
  return;
}
