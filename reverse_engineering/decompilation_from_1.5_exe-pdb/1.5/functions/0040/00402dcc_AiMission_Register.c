/*
 * Entry: 00402dcc
 * Name: AiMission::Register
 * Namespace: AiMission
 * Signature: void Register(AiMissionClass * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AiMission::Register(AiMissionClass *param_1)

{
  list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *this;
  
  if (missions == (list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *)0x0) {
    this = operator_new(0x1c);
    if (this == (list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *)0x0) {
      missions = (list<AiMissionClass_*,std::allocator<AiMissionClass_*>_> *)0x0;
    }
    else {
      missions = std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::
                 list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>(this);
    }
  }
  std::list<AiMissionClass_*,std::allocator<AiMissionClass_*>_>::push_back(missions,&param_1);
  return;
}
