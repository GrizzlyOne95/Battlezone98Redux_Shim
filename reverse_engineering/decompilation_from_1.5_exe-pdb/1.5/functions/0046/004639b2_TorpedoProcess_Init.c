/*
 * Entry: 004639b2
 * Name: TorpedoProcess::Init
 * Namespace: TorpedoProcess
 * Signature: void Init(TorpedoProcess * this, AiMission * param_1, GameObject * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall TorpedoProcess::Init(TorpedoProcess *this,AiMission *param_1,GameObject *param_2)

{
  AiProcess::Init((AiProcess *)this,param_1,param_2);
  GameObject::GetWhat(param_2);
  return;
}
