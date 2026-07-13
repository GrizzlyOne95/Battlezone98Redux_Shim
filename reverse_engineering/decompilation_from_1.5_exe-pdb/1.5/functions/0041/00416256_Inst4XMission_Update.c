/*
 * Entry: 00416256
 * Name: Inst4XMission::Update
 * Namespace: Inst4XMission
 * Signature: void Update(Inst4XMission * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Inst4XMission::Update(Inst4XMission *this)

{
  LuaMission::Update((LuaMission *)this);
  Execute(this);
  return;
}
