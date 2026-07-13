/*
 * Entry: 0043a254
 * Name: Misn15Mission::Update
 * Namespace: Misn15Mission
 * Signature: void Update(Misn15Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn15Mission::Update(Misn15Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
