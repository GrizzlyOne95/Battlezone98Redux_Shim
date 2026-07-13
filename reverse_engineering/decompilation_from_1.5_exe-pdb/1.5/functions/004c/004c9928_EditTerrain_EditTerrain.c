/*
 * Entry: 004c9928
 * Name: EditTerrain::EditTerrain
 * Namespace: EditTerrain
 * Signature: EditTerrain * EditTerrain(EditTerrain * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

EditTerrain * __thiscall EditTerrain::EditTerrain(EditTerrain *this)

{
  DisplayInterface::DisplayInterface((DisplayInterface *)this);
  this->_padding_ = (int)&_vftable_;
  DisplayInterface::AddView((DisplayInterface *)this,10,0);
  return this;
}
