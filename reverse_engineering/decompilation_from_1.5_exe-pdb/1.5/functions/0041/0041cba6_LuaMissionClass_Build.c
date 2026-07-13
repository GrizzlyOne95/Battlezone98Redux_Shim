/*
 * Entry: 0041cba6
 * Name: LuaMissionClass::Build
 * Namespace: LuaMissionClass
 * Signature: AiMission * Build(LuaMissionClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

AiMission * __thiscall LuaMissionClass::Build(LuaMissionClass *this)

{
  LuaMission *pLVar1;
  
  pLVar1 = operator_new(0x48);
  if (pLVar1 != (LuaMission *)0x0) {
    pLVar1 = LuaMission::LuaMission(pLVar1);
    return (AiMission *)pLVar1;
  }
  return (AiMission *)0x0;
}
