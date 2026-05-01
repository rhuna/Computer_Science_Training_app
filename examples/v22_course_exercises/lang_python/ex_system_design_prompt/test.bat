@echo off
python main.py | findstr /C:"PASS_SYSTEM_DESIGN_PROMPT"
