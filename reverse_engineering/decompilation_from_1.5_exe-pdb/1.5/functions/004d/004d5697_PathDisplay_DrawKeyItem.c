/*
 * Entry: 004d5697
 * Name: PathDisplay::DrawKeyItem
 * Namespace: PathDisplay
 * Signature: void DrawKeyItem(PathDisplay * this, long param_1, long param_2, int param_3, char * param_4, long param_5, long param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
PathDisplay::DrawKeyItem
          (PathDisplay *this,long param_1,long param_2,int param_3,char *param_4,long param_5,
          long param_6)

{
  PathDisplay *local_c;
  PathDisplay *local_8;
  
  local_c = this;
  local_8 = this;
  Font_Get_String_Dimensions(DisplayInterface::textFont,param_4,(long *)&local_c,(long *)&local_8);
  if (param_3 == 0) {
    Graphic_Rect_Filled(DisplayInterface::currentBuffer,param_1,param_2,
                        (int)&local_c->_padding_ + param_1,(int)&local_8->_padding_ + param_2,
                        param_6,SOLID_PIXELS);
  }
  else {
    Graphic_Rect_Filled(DisplayInterface::currentBuffer,param_1 + -5,param_2,
                        (int)&local_c->_padding_ + param_1,(int)&local_8->_padding_ + param_2,
                        param_6,SOLID_PIXELS);
    DrawSprite(DisplayInterface::currentBuffer,param_3,param_1 + -4,param_2,0x20001);
  }
  Font_Set_Foreground(DisplayInterface::textFont,param_5);
  Font_Print_String(DisplayInterface::textFont,DisplayInterface::currentBuffer,param_1,param_2,
                    param_4);
  return;
}
