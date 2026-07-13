/*
 * Entry: 0049f616
 * Name: Howitzer::Load
 * Namespace: Howitzer
 * Signature: bool Load(Howitzer * this, _iobuf * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Howitzer::Load(Howitzer *this,_iobuf *param_1)

{
  bool bVar1;
  
  if (version < 0x3fc) {
    bVar1 = HoverCraft::Load((HoverCraft *)this,param_1);
    return bVar1;
  }
  bVar1 = TurretTank::Load((TurretTank *)this,param_1);
  return bVar1;
}
