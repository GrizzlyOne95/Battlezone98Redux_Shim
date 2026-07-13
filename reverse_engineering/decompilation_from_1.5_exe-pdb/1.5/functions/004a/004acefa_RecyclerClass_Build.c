/*
 * Entry: 004acefa
 * Name: RecyclerClass::Build
 * Namespace: RecyclerClass
 * Signature: GameObject * Build(RecyclerClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall RecyclerClass::Build(RecyclerClass *this,_OBJ76 *param_1)

{
  Recycler *pRVar1;
  
  pRVar1 = GameObject::operator_new(800);
  if (pRVar1 == (Recycler *)0x0) {
    pRVar1 = (Recycler *)0x0;
  }
  else {
    pRVar1 = Recycler::Recycler(pRVar1,param_1,this);
  }
  return (GameObject *)pRVar1;
}
