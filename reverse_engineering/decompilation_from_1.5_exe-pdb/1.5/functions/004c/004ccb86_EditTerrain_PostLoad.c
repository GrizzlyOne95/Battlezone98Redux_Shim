/*
 * Entry: 004ccb86
 * Name: EditTerrain::PostLoad
 * Namespace: EditTerrain
 * Signature: void PostLoad(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::PostLoad(EditTerrain *this)

{
  long *plVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  long lVar5;
  int iVar6;
  
  this->colorBLACK = 0;
  lVar5 = Get_Closest_RGB_Entry(0.3,0.3,0.3);
  this->colorDKGREY = lVar5;
  lVar5 = Get_Closest_RGB_Entry(0.6,0.6,0.6);
  this->colorLTGREY = lVar5;
  lVar5 = Get_Closest_RGB_Entry(1.0,1.0,1.0);
  this->colorWHITE = lVar5;
  InitStatusLine(this);
  CreateMenu(this,&tileMenu);
  CreateMenu(this,&gridMenu);
  iVar6 = GetSpriteIndex("edit_but.0");
  this->bgIndex = iVar6;
  this->brushWidth = 0;
  this->brushDepth = 0;
  this->brushState = 0;
  this->brushY = (float)this->eyedropGrid * 0.1;
  this->brushInc = 0.1;
  this->brushSD = 1.0;
  (this->brushRect).left = gridMenu.rect.left;
  plVar1 = &(this->brushRect).top;
  *plVar1 = gridMenu.rect.bottom + 8;
  iVar3 = (this->brushRect).left;
  iVar4 = *plVar1;
  iVar6 = iVar3 + 0x85;
  iVar2 = iVar4 + 0x85;
  (this->brushRect).right = iVar6;
  (this->brushRect).bottom = iVar2;
  this->brushDX = (iVar6 - iVar3) + 1;
  this->brushDY = (iVar2 - iVar4) + 1;
  return;
}
