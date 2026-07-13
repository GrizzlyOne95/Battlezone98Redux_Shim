/*
 * Entry: 0042bc30
 * Name: Misn07Mission::Update
 * Namespace: Misn07Mission
 * Signature: void Update(Misn07Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn07Mission::Update(Misn07Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
