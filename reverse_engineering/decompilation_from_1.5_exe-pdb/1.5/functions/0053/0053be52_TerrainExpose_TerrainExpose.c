/*
 * Entry: 0053be52
 * Name: TerrainExpose::TerrainExpose
 * Namespace: TerrainExpose
 * Signature: TerrainExpose * TerrainExpose(TerrainExpose * this, _OBJ76 * param_1, TerrainExposeClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

TerrainExpose * __thiscall
TerrainExpose::TerrainExpose(TerrainExpose *this,_OBJ76 *param_1,TerrainExposeClass *param_2)

{
  SpecialItem::SpecialItem((SpecialItem *)this,param_1,(SpecialItemClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  this->active = false;
  return this;
}
