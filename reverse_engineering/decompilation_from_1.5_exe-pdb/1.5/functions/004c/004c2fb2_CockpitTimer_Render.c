/*
 * Entry: 004c2fb2
 * Name: CockpitTimer::Render
 * Namespace: CockpitTimer
 * Signature: void Render(CockpitTimer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall CockpitTimer::Render(CockpitTimer *this)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_48;
  int local_44;
  int local_40;
  int local_3c;
  int local_38;
  int local_8;
  
  iVar7 = this->timer;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  iVar2 = iVar7;
  if (0 < iVar7) {
    iVar2 = iVar7 / 10;
    local_38 = iVar7 % 10;
    if (0 < iVar2) {
      iVar3 = iVar2 / 6;
      local_3c = iVar2 % 6;
      iVar2 = iVar3;
      if (0 < iVar3) {
        iVar2 = iVar3 / 10;
        local_40 = iVar3 % 10;
      }
    }
  }
  if (this->hours == false) {
    if (0 < iVar2) {
      local_44 = iVar2;
    }
  }
  else if (0 < iVar2) {
    local_44 = iVar2 % 6;
    if (0 < iVar2 / 6) {
      local_48 = iVar2 / 6;
    }
  }
  if (this->countdown == false) {
    if (iVar7 < this->warn) goto LAB_004c3074;
    if (iVar7 < this->alert) goto LAB_004c307e;
  }
  else {
    if (this->warn < iVar7) {
LAB_004c3074:
      iVar7 = this->index[0];
      goto LAB_004c3033;
    }
    if (this->alert < iVar7) {
LAB_004c307e:
      iVar7 = this->index[1];
      goto LAB_004c3033;
    }
  }
  iVar7 = this->index[2];
LAB_004c3033:
  iVar4 = GetSpriteWidth(this->title);
  iVar3 = GetSpriteWidth(iVar7);
  iVar5 = GetSpriteHeight(iVar7);
  iVar2 = GetSpriteWidth(iVar7 + 10);
  fVar1 = spriteZ;
  if (this->hours == false) {
    iVar6 = iVar2 + 9 + iVar3 * 4;
  }
  else {
    iVar6 = iVar3 * 5 + 0xc + iVar2 * 2;
  }
  iVar4 = Device.Viewport.Width - iVar4;
  local_8 = (Device.Viewport.Width - iVar6) / 2;
  if (400 < Device.Viewport.Width) {
    spriteZ = spriteZ + 0.01;
    Clipped_Rect_Filled(DisplayInterface::currentBuffer,local_8 + -2,8,local_8 + 2 + iVar6,
                        iVar5 + 0x16,DisplayInterface::colorBlack,SOLID_PIXELS);
  }
  spriteZ = fVar1;
  DrawSprite(DisplayInterface::currentBuffer,this->title,iVar4 / 2,10,1);
  if (this->hours != false) {
    DrawSprite(DisplayInterface::currentBuffer,local_48 + iVar7,local_8,0x14,4);
    iVar4 = local_8 + 2 + iVar3;
    DrawSprite(DisplayInterface::currentBuffer,iVar7 + 10,iVar4,
               ((int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2) + 0x14,0x40004);
    DrawSprite(DisplayInterface::currentBuffer,iVar7 + 10,iVar4,
               ((int)(iVar5 * 3 + (iVar5 * 3 >> 0x1f & 3U)) >> 2) + 0x14,0x40004);
    local_8 = iVar4 + 3 + iVar2;
  }
  DrawSprite(DisplayInterface::currentBuffer,local_44 + iVar7,local_8,0x14,4);
  iVar4 = local_8 + 2 + iVar3;
  DrawSprite(DisplayInterface::currentBuffer,local_40 + iVar7,iVar4,0x14,4);
  iVar4 = iVar4 + 2 + iVar3;
  DrawSprite(DisplayInterface::currentBuffer,iVar7 + 10,iVar4,
             ((int)(iVar5 + (iVar5 >> 0x1f & 3U)) >> 2) + 0x14,0x40004);
  DrawSprite(DisplayInterface::currentBuffer,iVar7 + 10,iVar4,
             ((int)(iVar5 * 3 + (iVar5 * 3 >> 0x1f & 3U)) >> 2) + 0x14,0x40004);
  iVar2 = iVar4 + 3 + iVar2;
  DrawSprite(DisplayInterface::currentBuffer,local_3c + iVar7,iVar2,0x14,4);
  DrawSprite(DisplayInterface::currentBuffer,iVar7 + local_38,iVar2 + 2 + iVar3,0x14,4);
  return;
}
