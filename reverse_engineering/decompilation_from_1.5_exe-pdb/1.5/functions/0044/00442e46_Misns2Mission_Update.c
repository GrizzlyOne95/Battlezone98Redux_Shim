/*
 * Entry: 00442e46
 * Name: Misns2Mission::Update
 * Namespace: Misns2Mission
 * Signature: void Update(Misns2Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns2Mission::Update(Misns2Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
