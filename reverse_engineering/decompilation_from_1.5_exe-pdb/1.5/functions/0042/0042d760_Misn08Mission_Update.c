/*
 * Entry: 0042d760
 * Name: Misn08Mission::Update
 * Namespace: Misn08Mission
 * Signature: void Update(Misn08Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn08Mission::Update(Misn08Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
