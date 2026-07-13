/*
 * Entry: 0053bec4
 * Name: TerrainExpose::Activate
 * Namespace: TerrainExpose
 * Signature: void Activate(TerrainExpose * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TerrainExpose::Activate(TerrainExpose *this)

{
  tagENTITY *ptVar1;
  tagENTITY *ptVar2;
  
  this->active = true;
  ptVar1 = (tagENTITY *)(**(code **)(*(int *)(this->_padding_ + 0x20) + 0x2c))();
  ptVar2 = Get_Camera_Owner();
  if (ptVar2 == ptVar1) {
    ColorFade::SetFade(&colorFade,1.0,1.0,0xff,0xff,0xff);
  }
  return;
}
