/*
 * Entry: 004145b6
 * Name: GoNear::DrawStateA
 * Namespace: GoNear
 * Signature: void DrawStateA(GoNear * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GoNear::DrawStateA(GoNear *this)

{
  float fVar1;
  float fVar2;
  WorldInterface *pWVar3;
  GameObject *pGVar4;
  float *pfVar5;
  undefined1 local_18 [4];
  long local_14;
  int local_10;
  GoNear *local_c;
  int local_8;
  
  local_c = this;
  pGVar4 = GameObjectHandle::GetObj(this->_padding_);
  this->_padding_ = (int)pGVar4;
  pWVar3 = WorldInterface::currentDisplay;
  if (pGVar4 != (GameObject *)0x0) {
    pfVar5 = (float *)(**(code **)(pGVar4->_padding_ + 0xc))();
    fVar1 = *pfVar5;
    fVar2 = pfVar5[2];
    (**(code **)(*(int *)pWVar3 + 0x20))(fVar1,fVar2,&local_8,&local_14);
    (**(code **)(*(int *)pWVar3 + 0x20))(SQRT(local_c->nearSq) + fVar1,fVar2,&local_10,local_18);
    Graphic_Circle(DisplayInterface::currentBuffer,local_8,local_14,local_10 - local_8,0x18,
                   DisplayInterface::colorYellow,SOLID_PIXELS);
  }
  return;
}
