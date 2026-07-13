/*
 * Entry: 00423292
 * Name: Misn04Mission::Update
 * Namespace: Misn04Mission
 * Signature: void Update(Misn04Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn04Mission::Update(Misn04Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
