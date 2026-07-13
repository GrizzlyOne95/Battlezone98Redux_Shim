/*
 * Entry: 004403f8
 * Name: Misns1Mission::Update
 * Namespace: Misns1Mission
 * Signature: void Update(Misns1Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns1Mission::Update(Misns1Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
