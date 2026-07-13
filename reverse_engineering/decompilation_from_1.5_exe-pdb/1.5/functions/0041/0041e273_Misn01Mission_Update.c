/*
 * Entry: 0041e273
 * Name: Misn01Mission::Update
 * Namespace: Misn01Mission
 * Signature: void Update(Misn01Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn01Mission::Update(Misn01Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
