/*
 * Entry: 00465d2c
 * Name: Tran05Mission::Update
 * Namespace: Tran05Mission
 * Signature: void Update(Tran05Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran05Mission::Update(Tran05Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
