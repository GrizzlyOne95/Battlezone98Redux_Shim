/*
 * Entry: 004b4300
 * Name: TurretCraft::Init
 * Namespace: TurretCraft
 * Signature: void Init(TurretCraft * this, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TurretCraft::Init(TurretCraft *this,int param_1)

{
  Craft::Init((Craft *)this,param_1);
  if (this->powerSource != 0) {
    SetHazard(this);
  }
  return;
}
