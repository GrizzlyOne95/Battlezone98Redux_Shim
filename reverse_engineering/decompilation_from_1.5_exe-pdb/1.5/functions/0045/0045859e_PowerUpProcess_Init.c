/*
 * Entry: 0045859e
 * Name: PowerUpProcess::Init
 * Namespace: PowerUpProcess
 * Signature: void Init(PowerUpProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PowerUpProcess::Init(PowerUpProcess *this,AiMission *param_1,GameObject *param_2)

{
  AiProcess::Init((AiProcess *)this,param_1,param_2);
  GameObject::GetWhat(param_2);
  return;
}
