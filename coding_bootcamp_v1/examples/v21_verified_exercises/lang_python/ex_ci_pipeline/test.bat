@echo off
python main.py | findstr /C:"PASS_CI_PIPELINE"
