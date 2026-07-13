/*
 * Entry: 00414b9d
 * Name: GoNearAndSit::GoNearAndSit
 * Namespace: GoNearAndSit
 * Signature: GoNearAndSit * GoNearAndSit(GoNearAndSit * this, Craft * param_1, GameObject * param_2, float param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GoNearAndSit * __thiscall
GoNearAndSit::GoNearAndSit(GoNearAndSit *this,Craft *param_1,GameObject *param_2,float param_3)

{
  GoNear::GoNear((GoNear *)this,param_1,param_2,param_3);
  *(undefined ***)this = &_vftable_;
  return this;
}
