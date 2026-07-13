/*
 * Entry: 0044529b
 * Name: Misns5Mission::Update
 * Namespace: Misns5Mission
 * Signature: void Update(Misns5Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns5Mission::Update(Misns5Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
