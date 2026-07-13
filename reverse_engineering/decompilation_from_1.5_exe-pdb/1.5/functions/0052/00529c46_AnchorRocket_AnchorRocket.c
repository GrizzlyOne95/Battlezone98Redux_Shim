/*
 * Entry: 00529c46
 * Name: AnchorRocket::AnchorRocket
 * Namespace: AnchorRocket
 * Signature: AnchorRocket * AnchorRocket(AnchorRocket * this, _OBJ76 * param_1, AnchorRocketClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AnchorRocket * __thiscall
AnchorRocket::AnchorRocket(AnchorRocket *this,_OBJ76 *param_1,AnchorRocketClass *param_2)

{
  Rocket::Rocket((Rocket *)this,param_1,(RocketClass *)param_2);
  this->_padding_ = (int)&_vftable_;
  return this;
}
