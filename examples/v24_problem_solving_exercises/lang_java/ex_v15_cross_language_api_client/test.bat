@echo off
javac Main.java || exit /b 1
java Main | findstr /C:"PASS_V15_CROSS_LANGUAGE_API_CLIENT"
