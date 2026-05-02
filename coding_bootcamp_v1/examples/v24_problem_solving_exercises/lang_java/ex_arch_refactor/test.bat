@echo off
javac Main.java || exit /b 1
java Main | findstr /C:"PASS_ARCH_REFACTOR"
