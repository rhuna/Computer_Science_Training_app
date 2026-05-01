@echo off
javac Main.java || exit /b 1
java Main | findstr /C:"PASS_SAFE_LOGIN_REVIEW"
