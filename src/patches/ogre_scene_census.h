#pragma once
// LOCAL DIAGNOSTIC (scene leak hunt). OPENSHIM_SCENE_CENSUS=1.

namespace BZROpenShim
{
    namespace Hooks
    {
        bool SceneCensusEnabled();
        void SceneCensusOnVisit(const void* movableObject, const void* camera, bool onlyShadowCasters);
        void SceneCensusTick();
    }
}
