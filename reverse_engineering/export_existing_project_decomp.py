from __future__ import annotations

import argparse
import re
from pathlib import Path
from time import time

from pyghidra import HeadlessPyGhidraLauncher, open_program


def get_filename(func) -> str:
    name = re.sub(r'[<>:"/\\\\|?*]', "_", func.getName()[:80]).rstrip(" .")
    return f"{name}-{func.getEntryPoint()}"


def setup_decompiler(program):
    from ghidra.app.decompiler import DecompInterface, DecompileOptions

    options = DecompileOptions()
    options.grabFromProgram(program)
    iface = DecompInterface()
    iface.setOptions(options)
    iface.openProgram(program)
    return iface


def decompile_func(func, decompiler, monitor, timeout_secs: int):
    result = decompiler.decompileFunction(func, timeout_secs, monitor)
    if result.getErrorMessage():
        code = result.getErrorMessage()
        signature = ""
    else:
        code = result.decompiledFunction.getC()
        signature = result.decompiledFunction.getSignature() or ""
    return get_filename(func), code, str(signature)


def main() -> None:
    parser = argparse.ArgumentParser(description="Decompile an existing analyzed Ghidra project without re-running analysis.")
    parser.add_argument("--binary", type=Path, required=True)
    parser.add_argument("--project-path", type=Path, required=True)
    parser.add_argument("--project-name", required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--max-ram-percent", type=float, default=40.0)
    parser.add_argument("--skip-cache", action="store_true")
    parser.add_argument("--limit", type=int, default=0)
    parser.add_argument("--decompile-timeout-secs", type=int, default=30)
    args = parser.parse_args()

    output_dir = args.output_dir.resolve()
    output_dir.mkdir(parents=True, exist_ok=True)

    launcher = HeadlessPyGhidraLauncher(False)
    launcher.add_vmargs(f"-XX:MaxRAMPercentage={args.max_ram_percent}")
    launcher.start()

    from ghidra.util.task import ConsoleTaskMonitor

    with open_program(args.binary.resolve(), project_location=args.project_path.resolve(), project_name=args.project_name, analyze=False) as flat_api:
        program = flat_api.getCurrentProgram()
        all_funcs = list(program.getFunctionManager().getFunctions(True))
        if args.limit > 0:
            all_funcs = all_funcs[: args.limit]
        monitor = ConsoleTaskMonitor()
        decompiler = setup_decompiler(program)

        start = time()
        completed = 0

        def should_write(func) -> bool:
            return args.skip_cache or not (output_dir / f"{get_filename(func)}.c").exists()

        for func in all_funcs:
            if not should_write(func):
                continue
            name = get_filename(func)
            try:
                name, code, signature = decompile_func(func, decompiler, monitor, args.decompile_timeout_secs)
            except Exception as exc:
                (output_dir / f"{name}.err").write_text(str(exc) + "\n", encoding="utf-8", errors="replace")
                completed += 1
                if completed and completed % 250 == 0:
                    print(f"processed {completed}/{len(all_funcs)}")
                continue
            (output_dir / f"{name}.c").write_text(code, encoding="utf-8", errors="replace")
            if signature:
                (output_dir / f"{name}.sig").write_text(signature + "\n", encoding="utf-8")
            completed += 1
            if completed and completed % 250 == 0:
                print(f"processed {completed}/{len(all_funcs)}")

        print(f"processed {completed} functions in {time() - start:.1f}s")
        print(output_dir)


if __name__ == "__main__":
    main()
