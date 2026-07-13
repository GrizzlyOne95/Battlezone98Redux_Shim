/*
 * Entry: 004319e8
 * Name: Misn10Mission::Update
 * Namespace: Misn10Mission
 * Signature: void Update(Misn10Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn10Mission::Update(Misn10Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
