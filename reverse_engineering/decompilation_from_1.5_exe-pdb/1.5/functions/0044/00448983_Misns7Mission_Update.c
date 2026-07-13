/*
 * Entry: 00448983
 * Name: Misns7Mission::Update
 * Namespace: Misns7Mission
 * Signature: void Update(Misns7Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misns7Mission::Update(Misns7Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
