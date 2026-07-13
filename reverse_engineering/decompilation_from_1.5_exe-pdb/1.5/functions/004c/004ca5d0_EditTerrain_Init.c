/*
 * Entry: 004ca5d0
 * Name: EditTerrain::Init
 * Namespace: EditTerrain
 * Signature: void Init(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::Init(EditTerrain *this)

{
  TEXTURE *pTVar1;
  _GRAPHIC_BUFFER *p_Var2;
  float (*pafVar3) [17];
  int iVar4;
  int iVar5;
  long *plVar6;
  float (*pafVar7) [17];
  float10 fVar8;
  undefined1 local_98 [64];
  long local_58 [13];
  float local_24;
  float local_20;
  float local_1c;
  float (*local_18) [17];
  int local_14;
  float local_10;
  float local_c;
  float (*local_8) [17];
  
  (this->viewCenter).x = 0.0;
  (this->viewCenter).y = 0.0;
  (this->viewCenter).z = 0.0;
  this->viewZoom = 8.0;
  this->Yaw0 = 0.0;
  this->Yaw = 0.0;
  this->Pitch0 = 0.5235988;
  this->Pitch = 0.5235988;
  GetCameraMatrix(this,(MAT_3D *)local_98);
  this->lastMenu = &tileMenu;
  this->eyedropTile = 0;
  this->eyedropGrid = 999;
  this->lastLButton = 0;
  this->lastRButton = 0;
  arrowCursor.index = GetSpriteIndex(arrowCursor.name);
  this->mapDX = 0x80;
  this->mapDY = 0x80;
  pTVar1 = malloc(0x4008);
  this->txMap = pTVar1;
  if (pTVar1 == (TEXTURE *)0x0) {
    DEBUG_systemWarning("Could not create world map buffer in EditTerrain\n");
  }
  this->txMap->width = (short)this->mapDX;
  this->txMap->height = this->mapDY;
  this->txMap->type = 0;
  p_Var2 = Graphic_Buffer_Init_Ex
                     ((_GRAPHIC_BUFFER *)(local_98 + 0xc),this->mapDX,this->mapDY,
                      (char *)(this->txMap + 1),BYTES_FORMAT);
  plVar6 = local_58;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    *plVar6 = p_Var2->Width;
    p_Var2 = (_GRAPHIC_BUFFER *)&p_Var2->Height;
    plVar6 = plVar6 + 1;
  }
  this->bellSD = -1.0;
  local_1c = 0.0;
  plVar6 = local_58;
  p_Var2 = &this->gbMap;
  for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
    p_Var2->Width = *plVar6;
    plVar6 = plVar6 + 1;
    p_Var2 = (_GRAPHIC_BUFFER *)&p_Var2->Height;
  }
  this->bellWidth = -1;
  this->bellDepth = -1;
  this->copyWidth = -1;
  this->copyDepth = -1;
  local_18 = this->blur;
  this->mapMaterials = 0;
  this->mapState = 0;
  this->undoCount = 0;
  this->undoStart = 0;
  this->undoEnd = 0;
  this->undoGCount = 0;
  this->undoGStart = 0;
  this->undoGEnd = 0;
  this->blurSD = 1;
  this->blurWidth = 6;
  local_14 = 0;
  local_24 = 0.3989423;
  local_c = -3.0;
  do {
    iVar4 = 0;
    local_10 = (float)this->blurWidth * -0.5;
    if (-1 < this->blurWidth) {
      local_8 = local_18;
      local_20 = local_c * local_c;
      do {
        fVar8 = (float10)__CIexp();
        (*local_8)[0] = (float)(fVar8 * (float10)local_24);
        iVar4 = iVar4 + 1;
        local_1c = (float)(fVar8 * (float10)local_24 + (float10)local_1c);
        local_10 = local_10 + 1.0;
        local_8 = (float (*) [17])(*local_8 + 1);
      } while (iVar4 <= this->blurWidth);
    }
    local_14 = local_14 + 1;
    local_c = local_c + 1.0;
    local_18 = local_18 + 1;
  } while (local_14 <= this->blurWidth);
  iVar4 = 0;
  if (-1 < this->blurWidth) {
    pafVar7 = this->blur;
    do {
      iVar5 = 0;
      pafVar3 = pafVar7;
      if (-1 < this->blurWidth) {
        do {
          iVar5 = iVar5 + 1;
          (*pafVar3)[0] = (*pafVar3)[0] * (1.0 / local_1c);
          pafVar3 = (float (*) [17])(*pafVar3 + 1);
        } while (iVar5 <= this->blurWidth);
      }
      iVar4 = iVar4 + 1;
      pafVar7 = pafVar7 + 1;
    } while (iVar4 <= this->blurWidth);
  }
  return;
}
