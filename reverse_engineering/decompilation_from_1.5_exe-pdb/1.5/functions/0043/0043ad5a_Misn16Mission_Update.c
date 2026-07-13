/*
 * Entry: 0043ad5a
 * Name: Misn16Mission::Update
 * Namespace: Misn16Mission
 * Signature: void Update(Misn16Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn16Mission::Update(Misn16Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
