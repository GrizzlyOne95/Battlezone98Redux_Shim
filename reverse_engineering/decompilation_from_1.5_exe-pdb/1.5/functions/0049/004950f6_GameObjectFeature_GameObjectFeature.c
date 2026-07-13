/*
 * Entry: 004950f6
 * Name: GameObjectFeature::GameObjectFeature
 * Namespace: GameObjectFeature
 * Signature: GameObjectFeature * GameObjectFeature(GameObjectFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObjectFeature * __thiscall GameObjectFeature::GameObjectFeature(GameObjectFeature *this)

{
  GameFeature::GameFeature((GameFeature *)this);
  *(byte *)&this->_padding_ = (byte)this->_padding_ | 1;
  this->_padding_ = (int)&_vftable_;
  return this;
}
