/*
 * Entry: 004b4c07
 * Name: TurretTank::SetActiveMode
 * Namespace: TurretTank
 * Signature: bool SetActiveMode(TurretTank * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TurretTank::SetActiveMode(TurretTank *this,int param_1)

{
  bool bVar1;
  
  if (param_1 == 4) {
    GameObject::SetCommand((GameObject *)this,CMD_DROPOFF);
    return true;
  }
  bVar1 = Craft::SetActiveMode((Craft *)this,param_1);
  return bVar1;
}
