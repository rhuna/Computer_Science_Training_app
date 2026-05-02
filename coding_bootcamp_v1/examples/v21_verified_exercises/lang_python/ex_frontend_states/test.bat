@echo off
python main.py | findstr /C:"PASS_FRONTEND_STATES"
