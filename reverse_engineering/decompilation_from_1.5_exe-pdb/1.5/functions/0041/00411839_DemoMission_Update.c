/*
 * Entry: 00411839
 * Name: DemoMission::Update
 * Namespace: DemoMission
 * Signature: void Update(DemoMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DemoMission::Update(DemoMission *this)

{
  AiMission::Update((AiMission *)this);
  Execute(this);
  return;
}
