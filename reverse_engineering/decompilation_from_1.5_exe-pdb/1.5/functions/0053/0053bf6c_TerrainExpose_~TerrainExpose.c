/*
 * Entry: 0053bf6c
 * Name: TerrainExpose::~TerrainExpose
 * Namespace: TerrainExpose
 * Signature: void ~TerrainExpose(TerrainExpose * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TerrainExpose::~TerrainExpose(TerrainExpose *this)

{
  this->_padding_ = (int)&_vftable_;
  if (this->active != false) {
    Deactivate(this);
  }
  SpecialItem::~SpecialItem((SpecialItem *)this);
  return;
}
