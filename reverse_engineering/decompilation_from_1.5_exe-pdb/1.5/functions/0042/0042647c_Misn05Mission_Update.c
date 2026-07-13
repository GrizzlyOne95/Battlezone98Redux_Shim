/*
 * Entry: 0042647c
 * Name: Misn05Mission::Update
 * Namespace: Misn05Mission
 * Signature: void Update(Misn05Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn05Mission::Update(Misn05Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
