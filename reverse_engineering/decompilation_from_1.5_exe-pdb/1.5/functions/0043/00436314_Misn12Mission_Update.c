/*
 * Entry: 00436314
 * Name: Misn12Mission::Update
 * Namespace: Misn12Mission
 * Signature: void Update(Misn12Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn12Mission::Update(Misn12Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
