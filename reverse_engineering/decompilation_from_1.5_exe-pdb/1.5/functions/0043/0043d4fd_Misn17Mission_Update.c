/*
 * Entry: 0043d4fd
 * Name: Misn17Mission::Update
 * Namespace: Misn17Mission
 * Signature: void Update(Misn17Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn17Mission::Update(Misn17Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
