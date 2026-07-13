/*
 * Entry: 00529c6d
 * Name: AnchorRocket::Init
 * Namespace: AnchorRocket
 * Signature: void Init(AnchorRocket * this, MAT_3D * param_1, _OBJ76 * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AnchorRocket::Init(AnchorRocket *this,MAT_3D *param_1,_OBJ76 *param_2)

{
  Rocket::Init((Rocket *)this,param_1,param_2);
  this->hitObj = 0;
  return;
}
