/*
 * Entry: 004397d3
 * Name: Misn14Mission::Update
 * Namespace: Misn14Mission
 * Signature: void Update(Misn14Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn14Mission::Update(Misn14Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
