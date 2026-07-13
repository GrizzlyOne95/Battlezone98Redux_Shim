/*
 * Entry: 0044418c
 * Name: Misns3Mission::Update
 * Namespace: Misns3Mission
 * Signature: void Update(Misns3Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns3Mission::Update(Misns3Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
