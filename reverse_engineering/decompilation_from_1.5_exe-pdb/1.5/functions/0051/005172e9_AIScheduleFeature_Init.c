/*
 * Entry: 005172e9
 * Name: AIScheduleFeature::Init
 * Namespace: AIScheduleFeature
 * Signature: void Init(AIScheduleFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall AIScheduleFeature::Init(AIScheduleFeature *this)

{
  attachIndex = gameObjectClass.attachCount;
  gameObjectClass.attachCount = gameObjectClass.attachCount + 1;
  return;
}
