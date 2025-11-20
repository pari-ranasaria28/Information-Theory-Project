#!/usr/bin/python
import subprocess
import os
import shutil

# Windows-safe function for deleting files
def safe_delete(pattern):
    # use PowerShell Remove-Item for wildcard support
    cmd = f'powershell -Command "Remove-Item -Force -ErrorAction SilentlyContinue {pattern}"'
    subprocess.call(cmd, shell=True)

# Windows-safe move
def safe_move(src, dst):
    try:
        os.remove(dst)
    except:
        pass
    shutil.move(src, dst)

C_LIST = []
for root, dirs, files in os.walk("../src/Constantes/"):
    for code in dirs:
        C_LIST.append(code)
    break

GCC_LIST = [""]   # keep empty because you use ICX (Windows)

print("Cleaning old executables...")
safe_delete("main.icc*")

for C in C_LIST:
    print(f"\n=== COMPILING CODE {C} ===")

    # Write constantes.h
    with open("../src/Constantes/constantes.h", "w") as f:
        f.write(f'#include "./{C}/constantes.h"\n')

    with open("../src/Constantes/constantes_sse.h", "w") as f:
        f.write(f'#include "./{C}/constantes_sse.h"\n')

    for COMPILER in GCC_LIST:
        print(f"COMPILATION OF LDPC DECODER FOR CODE [{C}]")

        # Clean previous build
        subprocess.call(f'make -f Makefile{COMPILER} clean', shell=True)

        # Build new decoder
        subprocess.call(f'make -f Makefile{COMPILER} -j 8', shell=True)

        # Move compiled main.exe to name main.icc.<C>
        if os.path.exists("main.exe"):
            out_name = f"main.icc.{C}"
            print(f"Output → {out_name}")
            safe_move("main.exe", out_name)
        else:
            print("ERROR: main.exe not produced. Check Makefile.")
