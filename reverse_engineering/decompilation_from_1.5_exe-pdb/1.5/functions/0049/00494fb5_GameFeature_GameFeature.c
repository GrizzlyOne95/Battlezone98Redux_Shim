/*
 * Entry: 00494fb5
 * Name: GameFeature::GameFeature
 * Namespace: GameFeature
 * Signature: GameFeature * GameFeature(GameFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameFeature * __thiscall GameFeature::GameFeature(GameFeature *this)

{
  vector<GameFeature_*,std::allocator<GameFeature_*>_> *this_00;
  GameFeature *local_8;
  
  this->_padding_ = (int)&_vftable_;
  this->gfName = (char *)0x0;
  this->initPriority = 0;
  this->cleanupPriority = 0;
  this->preLoadPriority = 0;
  this->postLoadPriority = 0;
  this->preDestroyPriority = 0;
  this->postRunPriority = 0;
  this->renderPriority = 0;
  this->field_0x24 = this->field_0x24 & 0xfe | 0xe;
  if (features == (vector<GameFeature_*,std::allocator<GameFeature_*>_> *)0x0) {
    local_8 = this;
    this_00 = operator_new(0x18);
    if (this_00 == (vector<GameFeature_*,std::allocator<GameFeature_*>_> *)0x0) {
      features = (vector<GameFeature_*,std::allocator<GameFeature_*>_> *)0x0;
    }
    else {
      features = std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::
                 vector<GameFeature_*,std::allocator<GameFeature_*>_>(this_00);
    }
  }
  local_8 = this;
  std::vector<GameFeature_*,std::allocator<GameFeature_*>_>::push_back(features,&local_8);
  return this;
}
