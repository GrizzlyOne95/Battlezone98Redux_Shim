/*
 * Entry: 0043ebfe
 * Name: Misn18Mission::Update
 * Namespace: Misn18Mission
 * Signature: void Update(Misn18Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn18Mission::Update(Misn18Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
