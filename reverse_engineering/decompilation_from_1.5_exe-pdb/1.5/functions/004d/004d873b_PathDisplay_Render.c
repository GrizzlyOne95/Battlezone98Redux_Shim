/*
 * Entry: 004d873b
 * Name: PathDisplay::Render
 * Namespace: PathDisplay
 * Signature: void Render(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall PathDisplay::Render(PathDisplay *this)

{
  float *pfVar1;
  long local_a4;
  float local_a0;
  float fStack_9c;
  float local_98;
  long local_94;
  float local_90;
  float local_8c;
  char local_88 [12];
  undefined1 local_7c [116];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_7c;
  WorldInterface::currentDisplay = (WorldInterface *)this;
  ComputeScale(this);
  Graphic_Buffer_Clear(DisplayInterface::currentBuffer,DisplayInterface::colorBlack);
  DrawColorLayer(this);
  HandleControlMode(this);
  DrawObjects(this);
  DrawMenuBar(this);
  if (GameObject::userObject != (GameObject *)0x0) {
    pfVar1 = (float *)(**(code **)(GameObject::userObject->_padding_ + 0xc))();
    local_a0 = *pfVar1;
    fStack_9c = pfVar1[1];
    local_98 = pfVar1[2];
    (**(code **)(this->_padding_ + 0x24))
              (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_8c,&local_90);
    sprintf(local_88," Pos: (X, Z) Cursor (%.2f %.2f) User (%.2f %.2f) Zoom (%.3f)",(double)local_8c
            ,(double)local_90,(double)local_a0,(double)local_98,(double)this->scale);
    Graphic_Text(DisplayInterface::currentBuffer,0xf,DisplayInterface::currentBuffer->Height + -0xf,
                 &local_a4,&local_94,local_88,DisplayInterface::textFont,
                 DisplayInterface::colorWhite,DisplayInterface::colorBlack,0,0,0);
  }
  WorldInterface::currentDisplay = (WorldInterface *)0x0;
  DisplayInterface::cursorIndex = CURSOR_MAP.index;
  return;
}
