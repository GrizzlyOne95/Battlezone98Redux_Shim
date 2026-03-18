import argparse
import json
import runpy
import sys
from pathlib import Path

import qiling


def cmd_version(_args: argparse.Namespace) -> int:
    payload = {
        "qiling_version": getattr(qiling, "__version__", ""),
        "module_path": str(Path(qiling.__file__).resolve()),
        "python": sys.executable,
    }
    print(json.dumps(payload, indent=2))
    return 0


def cmd_run_python(args: argparse.Namespace) -> int:
    script = Path(args.script).resolve()
    if not script.exists():
        raise FileNotFoundError(f"Script not found: {script}")

    sys.argv = [str(script), *args.script_args]
    runpy.run_path(str(script), run_name="__main__")
    return 0


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description="Small CLI bridge for the installed Qiling Python package."
    )
    subparsers = parser.add_subparsers(dest="command", required=True)

    version_parser = subparsers.add_parser("version", help="Print Qiling version and module path.")
    version_parser.set_defaults(func=cmd_version)

    run_parser = subparsers.add_parser(
        "run-python",
        help="Run a Python script in the current interpreter with Qiling available.",
    )
    run_parser.add_argument("script")
    run_parser.add_argument("script_args", nargs=argparse.REMAINDER)
    run_parser.set_defaults(func=cmd_run_python)

    return parser


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()
    return int(args.func(args))


if __name__ == "__main__":
    raise SystemExit(main())
