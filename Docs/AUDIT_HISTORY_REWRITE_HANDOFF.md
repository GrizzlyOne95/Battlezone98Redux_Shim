# History-cleanup handoff

Prepared during CodebaseAudit on September 27; recovered September 28, 2026.
**The history rewrite has not been executed against GitHub.** The owner's
latest decision is to keep OpenShim public. The old draft's recommendation to
make the repository private is superseded and is not an instruction to act.

## Completed preparation

- #281 removed the leaked PDB from the working tree; its private source is
  `Battlezone_Source/BZ1/Redux/bzrpdb.zip`.
- #373 removed the Redux corpus, LFS corpus archive, and prerelease executable
  tree from current OpenShim source. The private archive is
  `Battlezone_Source/BZ1/Redux/openshim_re_corpus/`.
- `reverse_engineering/Restore-ReCorpus.ps1` restores local research copies.
- The original coordinator ran a local `git filter-repo` dry run. Its recorded
  pack-size result was 75.39 MiB to 34.00 MiB, with a clean `git fsck` and no
  unintended source changes in the compared branch trees. Those are historical
  results, not a validation of today's moving branches/tags.
- The exact draft removal list is preserved in
  [audit_20260925/history_paths_to_remove.txt](audit_20260925/history_paths_to_remove.txt).
  This is a proposal for review, not permission to remove additional paths.

The original detailed runbook and removal list have also been copied out of
the temporary session directory to
`%USERPROFILE%\Documents\GIT\.research-archive\CodebaseAudit-20260928`.
The original is explicitly historical: its main-tree claims, branch/PR counts,
proposed visibility change, and old-to-new SHA mapping are stale.

The original mirror, filtered mirrors, ref maps, and pre-rewrite bundle remain
in the coordinator's `scratchpad/histrewrite` directory, whose location is in
[the recovery tracker](AUDIT_BACKLOG_STATUS.md). Do not upload those objects:
the untouched mirror and bundle contain the material being removed.

## Preconditions for a separately authorized execution

1. Obtain explicit approval for the exact path scope, shared-history rewrite,
   temporary branch-protection changes, and any Support request. The current
   recovery authorizes none of those actions. Extracted stock chunk meshes
   were flagged separately in the draft and are not included in the proposed
   removal list.
2. Coordinate a push freeze with the owner and every active workstream. The
   current tracker lists local-only commits, dirty worktrees, and open PRs;
   resolve their disposition without blanket staging, deletion, or force-push.
3. Verify the private archive and make fresh, offline backups of remote refs,
   old-history Git objects, LFS objects, release assets, protection settings,
   and local-only/untracked research. An old dry-run bundle is not enough.
4. Use a fresh mirror at the frozen remote state. Disable its push URL while
   filtering. Re-run the reviewed path removal, then verify removed objects,
   `git fsck`, branch trees, refs, and the new commit/ref maps.
5. Plan tag handling and workflow protection before any remote ref update.
   The release workflow reacts to `v*` tags; prevent unintended rebuilds or
   replacement of published release assets. Preserve byte-identical assets
   and version/hash pins used by Campaign Reimagined. Do not delete/recreate
   published tags as an incidental cleanup step.
6. Compare frozen remote refs immediately before the approved push. Any drift
   means stop and rebuild the plan. Use an explicit reviewed ref set; never
   mirror-push GitHub-owned pull-request refs.
7. Restore protection/workflow settings, verify refs and release-asset hashes,
   and migrate local worktrees using the newly generated maps. Old clones
   must not accidentally re-upload removed history.
8. Separately address GitHub-owned PR refs, cached views, and LFS retention.
   A branch/tag force-push alone does not establish that those copies are
   gone. Verify the current GitHub procedure at execution time, obtain the
   owner's approval for external requests, and record the observed result.

The stopping point is a preserved plan with explicit approval gates. No remote
visibility, protection, workflow, tag, release, or history settings were
changed by the recovery.
