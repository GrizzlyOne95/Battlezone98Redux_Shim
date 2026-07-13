/*
 * Entry: 00414b3f
 * Name: GoGet::GoGet
 * Namespace: GoGet
 * Signature: GoGet * GoGet(GoGet * this, Craft * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GoGet * __thiscall GoGet::GoGet(GoGet *this,Craft *param_1,GameObject *param_2)

{
  GoNear::GoNear((GoNear *)this,param_1,param_2,6.0);
  *(undefined4 *)&this->field_0x100 = 0x40a00000;
  *(undefined ***)this = &_vftable_;
  *(undefined4 *)&this->field_0x70 = 0x3f800000;
  return this;
}
