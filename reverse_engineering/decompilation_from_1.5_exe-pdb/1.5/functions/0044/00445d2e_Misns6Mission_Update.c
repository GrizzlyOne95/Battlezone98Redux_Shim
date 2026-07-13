/*
 * Entry: 00445d2e
 * Name: Misns6Mission::Update
 * Namespace: Misns6Mission
 * Signature: void Update(Misns6Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns6Mission::Update(Misns6Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
