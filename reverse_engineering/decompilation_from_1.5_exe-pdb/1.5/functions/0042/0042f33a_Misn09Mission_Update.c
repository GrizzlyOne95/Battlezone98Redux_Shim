/*
 * Entry: 0042f33a
 * Name: Misn09Mission::Update
 * Namespace: Misn09Mission
 * Signature: void Update(Misn09Mission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Misn09Mission::Update(Misn09Mission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
