/*
 * Entry: 00466ebf
 * Name: TugFriend::~TugFriend
 * Namespace: TugFriend
 * Signature: void ~TugFriend(TugFriend * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TugFriend::~TugFriend(TugFriend *this)

{
  *(undefined ***)this = &TugProcess::_vftable_;
  TugProcess::CleanState((TugProcess *)this);
  AiProcess::~AiProcess((AiProcess *)this);
  return;
}
