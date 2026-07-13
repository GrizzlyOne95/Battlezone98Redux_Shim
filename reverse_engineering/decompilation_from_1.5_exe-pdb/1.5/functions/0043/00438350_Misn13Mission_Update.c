/*
 * Entry: 00438350
 * Name: Misn13Mission::Update
 * Namespace: Misn13Mission
 * Signature: void Update(Misn13Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn13Mission::Update(Misn13Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
