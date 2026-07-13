/*
 * Entry: 0045f93d
 * Name: Damage
 * Namespace: Global
 * Signature: void Damage(int param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Damage(int param_1,long param_2)

{
  GameObject *pGVar1;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  if (pGVar1 != (GameObject *)0x0) {
    scriptDamage.dmg_value = (float)param_2;
    scriptDamage.damager = (_OBJ76 *)0x0;
    scriptDamage.dmg_source = (_OBJ76 *)0x0;
    scriptDmgNormal.x = 0.0;
    scriptDmgNormal.y = 1.0;
    scriptDamage._8_4_ = 1;
    scriptDmgNormal.z = 0.0;
    (**(code **)(pGVar1->_padding_ + 0x38))(&scriptDamage,&scriptDmgNormal);
  }
  return;
}
