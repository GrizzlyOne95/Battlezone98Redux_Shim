/*
 * Entry: 00414bc1
 * Name: GoNearAndSit::GoNearAndSit
 * Namespace: GoNearAndSit
 * Signature: GoNearAndSit * GoNearAndSit(GoNearAndSit * this, Craft * param_1, GameObject * param_2, AiPath * param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GoNearAndSit * __thiscall
GoNearAndSit::GoNearAndSit
          (GoNearAndSit *this,Craft *param_1,GameObject *param_2,AiPath *param_3,float param_4)

{
  GoNear::GoNear((GoNear *)this,param_1,param_2,param_3,param_4);
  *(undefined ***)this = &_vftable_;
  return this;
}
