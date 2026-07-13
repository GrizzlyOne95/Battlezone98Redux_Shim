/*
 * Entry: 004643ca
 * Name: Tran02Mission::Update
 * Namespace: Tran02Mission
 * Signature: void Update(Tran02Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Tran02Mission::Update(Tran02Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
