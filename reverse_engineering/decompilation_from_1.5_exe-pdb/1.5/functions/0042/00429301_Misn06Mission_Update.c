/*
 * Entry: 00429301
 * Name: Misn06Mission::Update
 * Namespace: Misn06Mission
 * Signature: void Update(Misn06Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn06Mission::Update(Misn06Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
