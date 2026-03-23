
void __thiscall FUN_0067aa50(Renderable *param_1,SceneManager *param_2,RenderSystem *param_3)

{
  (**(code **)(**(int **)(param_1 + 0xb4) + 8))();
  param_1[0xb8] = (Renderable)0x1;
  Ogre::Renderable::postRender(param_1,param_2,param_3);
  return;
}

