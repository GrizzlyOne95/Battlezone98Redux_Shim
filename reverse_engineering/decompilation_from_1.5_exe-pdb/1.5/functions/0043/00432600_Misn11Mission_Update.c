/*
 * Entry: 00432600
 * Name: Misn11Mission::Update
 * Namespace: Misn11Mission
 * Signature: void Update(Misn11Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn11Mission::Update(Misn11Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
