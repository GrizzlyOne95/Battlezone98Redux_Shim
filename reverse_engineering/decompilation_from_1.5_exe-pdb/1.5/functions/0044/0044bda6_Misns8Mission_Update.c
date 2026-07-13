/*
 * Entry: 0044bda6
 * Name: Misns8Mission::Update
 * Namespace: Misns8Mission
 * Signature: void Update(Misns8Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns8Mission::Update(Misns8Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
