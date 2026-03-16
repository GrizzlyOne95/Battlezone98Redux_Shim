from __future__ import annotations

import argparse
import csv
import json
import sys
from pathlib import Path

from pyghidra import HeadlessPyGhidraLauncher, open_program


def address_offset(address) -> int:
    return int(address.getOffset()) if address is not None else 0


def namespace_name(namespace) -> str:
    try:
        return namespace.getName(True)
    except Exception:
        try:
            return namespace.getName()
        except Exception:
            return ""


def export_inventory(binary_path: Path, project_path: Path, project_name: str, output_dir: Path, analyze_if_needed: bool, max_ram_percent: float) -> None:
    launcher = HeadlessPyGhidraLauncher(False)
    launcher.add_vmargs(f"-XX:MaxRAMPercentage={max_ram_percent}")
    launcher.start()

    from ghidra.app.script import GhidraScriptUtil
    from ghidra.program.flatapi import FlatProgramAPI
    from ghidra.program.util import GhidraProgramUtilities

    output_dir.mkdir(parents=True, exist_ok=True)

    with open_program(binary_path, project_location=project_path, project_name=project_name, analyze=False) as flat_api:
        program = flat_api.getCurrentProgram()

        if analyze_if_needed and GhidraProgramUtilities.shouldAskToAnalyze(program):
            GhidraScriptUtil.acquireBundleHostReference()
            try:
                FlatProgramAPI(program).analyzeAll(program)
                if hasattr(GhidraProgramUtilities, "setAnalyzedFlag"):
                    GhidraProgramUtilities.setAnalyzedFlag(program, True)
                else:
                    GhidraProgramUtilities.markProgramAnalyzed(program)
            finally:
                GhidraScriptUtil.releaseBundleHostReference()

        metadata = {
            "program_name": program.getName(),
            "executable_path": str(binary_path),
            "image_base": address_offset(program.getImageBase()),
            "language_id": str(program.getLanguageID()),
            "compiler": str(program.getCompiler()),
            "function_count": int(program.getFunctionManager().getFunctionCount()),
            "symbol_count": int(program.getSymbolTable().getNumSymbols()),
        }
        (output_dir / "program.json").write_text(json.dumps(metadata, indent=2), encoding="utf-8")

        with (output_dir / "functions.csv").open("w", newline="", encoding="utf-8") as handle:
            writer = csv.writer(handle)
            writer.writerow(
                [
                    "entry_va",
                    "entry_rva",
                    "name",
                    "namespace",
                    "signature",
                    "calling_convention",
                    "return_type",
                    "parameter_count",
                    "parameter_types",
                    "is_thunk",
                    "is_external",
                    "body_min_va",
                    "body_max_va",
                ]
            )
            image_base = metadata["image_base"]
            for function in program.getFunctionManager().getFunctions(True):
                entry_va = address_offset(function.getEntryPoint())
                body = function.getBody()
                signature = str(function.getSignature())
                params = [str(parameter.getDataType()) for parameter in function.getParameters()]
                writer.writerow(
                    [
                        entry_va,
                        entry_va - image_base,
                        function.getName(),
                        namespace_name(function.getParentNamespace()),
                        signature,
                        function.getCallingConventionName(),
                        str(function.getReturnType()),
                        len(params),
                        "; ".join(params),
                        bool(function.isThunk()),
                        bool(function.isExternal()),
                        address_offset(body.getMinAddress()),
                        address_offset(body.getMaxAddress()),
                    ]
                )

        with (output_dir / "symbols.csv").open("w", newline="", encoding="utf-8") as handle:
            writer = csv.writer(handle)
            writer.writerow(["name", "address_va", "address_rva", "symbol_type", "source", "namespace"])
            image_base = metadata["image_base"]
            symbol_table = program.getSymbolTable()
            for symbol in symbol_table.getAllSymbols(True):
                address = symbol.getAddress()
                va = address_offset(address)
                writer.writerow(
                    [
                        symbol.getName(),
                        va,
                        va - image_base if va else "",
                        str(symbol.getSymbolType()),
                        str(symbol.getSource()),
                        namespace_name(symbol.getParentNamespace()),
                    ]
                )


def main() -> None:
    parser = argparse.ArgumentParser(description="Export machine-readable metadata from an analyzed Ghidra program.")
    parser.add_argument("--binary", type=Path, required=True)
    parser.add_argument("--project-path", type=Path, required=True)
    parser.add_argument("--project-name", required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    parser.add_argument("--analyze-if-needed", action="store_true")
    parser.add_argument("--max-ram-percent", type=float, default=50.0)
    args = parser.parse_args()

    export_inventory(args.binary, args.project_path, args.project_name, args.output_dir, args.analyze_if_needed, args.max_ram_percent)


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:
        print(f"export_ghidra_inventory.py failed: {exc}", file=sys.stderr)
        raise
