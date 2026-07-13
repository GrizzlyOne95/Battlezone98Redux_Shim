/*
 * Entry: 00537b02
 * Name: RemoteDetonatorClass::Build
 * Namespace: RemoteDetonatorClass
 * Signature: Weapon * Build(RemoteDetonatorClass * this, _OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Weapon * __thiscall RemoteDetonatorClass::Build(RemoteDetonatorClass *this,_OBJ76 *param_1)

{
  RemoteDetonator *pRVar1;
  
  pRVar1 = operator_new(0xd0);
  if (pRVar1 == (RemoteDetonator *)0x0) {
    pRVar1 = (RemoteDetonator *)0x0;
  }
  else {
    pRVar1 = RemoteDetonator::RemoteDetonator(pRVar1,param_1,this);
  }
  return (Weapon *)pRVar1;
}
