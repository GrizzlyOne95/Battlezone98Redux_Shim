/*
 * Entry: 004ca3eb
 * Name: EditTerrain::InitStatusLine
 * Namespace: EditTerrain
 * Signature: void InitStatusLine(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EditTerrain::InitStatusLine(EditTerrain *this)

{
  long lVar1;
  
  lVar1 = Get_Closest_RGB_Entry(0.75,0.75,0.75);
  this->textBG = lVar1;
  lVar1 = Get_Closest_RGB_Entry(0.0,0.0,0.0);
  this->textFG = lVar1;
  this->textDY = Default_Font->char_height;
  this->textDX = 0x280;
  return;
}
