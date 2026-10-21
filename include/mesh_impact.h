#pragma once

// Mesh-accurate ordnance impacts (GOG only, opt-in, restart to apply).
//
// Visual tier, [Display] MeshAccurateImpacts: when the engine registers a
// shot hit on a craft, the shot segment is cast against the craft's own part
// meshes and the impact explosion's render position is moved onto the hull:
// to the point the shot strikes, or, for a sphere-only hit that misses the
// mesh, to the nearest hull point.
// Hit outcome, direct damage, splash centre and physics kick stay where the
// engine put them, so it is safe in multiplayer.
//
// Gameplay trial, [SinglePlayer] MeshAccurateHits: the mesh decides the hit.
// A shot that passes between parts keeps flying; a hit lands on the hull.
// Stands down in network games.
//
// See reverse_engineering/ordnance_hit_test_20261021.md.
namespace BZROpenShim::MeshImpact
{
    void InitializeGlobal(); // Reads the INI/env request and installs the hooks.
    void RefreshGate();      // Multiplayer gate for the gameplay trial.
    void Clear();            // Mission/scene seam: drop cached meshes, log stats.
}
