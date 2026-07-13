/*
 * Entry: 004ca442
 * Name: EditTerrain::UpdateStatusLine
 * Namespace: EditTerrain
 * Signature: void UpdateStatusLine(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall EditTerrain::UpdateStatusLine(EditTerrain *this)

{
  float fVar1;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  int iVar2;
  undefined4 uVar3;
  double dVar4;
  double dVar5;
  int iVar6;
  int iVar7;
  char local_108 [124];
  undefined1 local_8c [132];
  uint local_8;
  
  fVar1 = spriteZ;
  local_8 = __security_cookie ^ (uint)local_8c;
  iVar7 = this->currentZ;
  iVar6 = this->currentX;
  iVar2 = (DisplayInterface::currentBuffer->Pane).y1 - this->textDY;
  dVar5 = (double)this->brushInc;
  dVar4 = (double)this->brushY;
  _ftol2_sse();
  uVar3 = extraout_EAX;
  _ftol2_sse();
  sprintf(local_108,"[Y=%.1fm] [Width=%dm] [Depth=%dm] [Height=%.1fm] [Incr=%.1fm] (%d,%d)",
          (double)this->currentY,extraout_EAX_00,uVar3,dVar4,dVar5,iVar6,iVar7);
  spriteZ = fVar1 + 0.1;
  Clipped_Rect_Filled(DisplayInterface::currentBuffer,(DisplayInterface::currentBuffer->Pane).x0,
                      iVar2 + -4,(DisplayInterface::currentBuffer->Pane).x1,
                      (DisplayInterface::currentBuffer->Pane).y1,this->textBG,SOLID_PIXELS);
  Font_Set_Foreground(Default_Font,this->textFG);
  spriteZ = fVar1;
  Font_Print_String(Default_Font,DisplayInterface::currentBuffer,2,iVar2 + -2,local_108);
  return;
}
