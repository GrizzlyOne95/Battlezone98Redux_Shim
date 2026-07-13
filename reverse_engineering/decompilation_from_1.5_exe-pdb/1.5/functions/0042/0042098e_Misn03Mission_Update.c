/*
 * Entry: 0042098e
 * Name: Misn03Mission::Update
 * Namespace: Misn03Mission
 * Signature: void Update(Misn03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn03Mission::Update(Misn03Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
