/*
 * Entry: 004449b6
 * Name: Misns4Mission::Update
 * Namespace: Misns4Mission
 * Signature: void Update(Misns4Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns4Mission::Update(Misns4Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
