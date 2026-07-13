/*
 * Entry: 00464ad6
 * Name: Tran03Mission::Update
 * Namespace: Tran03Mission
 * Signature: void Update(Tran03Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran03Mission::Update(Tran03Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
