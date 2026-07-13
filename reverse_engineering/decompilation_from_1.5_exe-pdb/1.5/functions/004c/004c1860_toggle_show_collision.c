/*
 * Entry: 004c1860
 * Name: toggle_show_collision
 * Namespace: Global
 * Signature: void toggle_show_collision(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl toggle_show_collision(void)

{
  BoundingBox::Toggle(&boundingBox);
  return;
}
