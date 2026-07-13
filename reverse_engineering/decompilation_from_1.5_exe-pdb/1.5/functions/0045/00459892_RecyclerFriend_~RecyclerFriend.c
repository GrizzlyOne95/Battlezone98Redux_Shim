/*
 * Entry: 00459892
 * Name: RecyclerFriend::~RecyclerFriend
 * Namespace: RecyclerFriend
 * Signature: void ~RecyclerFriend(RecyclerFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RecyclerFriend::~RecyclerFriend(RecyclerFriend *this)

{
  this->_padding_ = (int)&RecyclerProcess::_vftable_;
  RecyclerProcess::CleanState((RecyclerProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
