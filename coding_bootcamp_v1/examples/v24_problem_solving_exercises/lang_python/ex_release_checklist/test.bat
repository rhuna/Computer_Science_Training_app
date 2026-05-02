@echo off
python main.py | findstr /C:"PASS_RELEASE_CHECKLIST"
