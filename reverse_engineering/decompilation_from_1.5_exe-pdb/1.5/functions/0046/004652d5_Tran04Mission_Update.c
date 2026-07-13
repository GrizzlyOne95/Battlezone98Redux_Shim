/*
 * Entry: 004652d5
 * Name: Tran04Mission::Update
 * Namespace: Tran04Mission
 * Signature: void Update(Tran04Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran04Mission::Update(Tran04Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
