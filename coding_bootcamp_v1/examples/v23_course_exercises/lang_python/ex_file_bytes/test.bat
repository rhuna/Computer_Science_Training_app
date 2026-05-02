@echo off
python main.py | findstr /C:"PASS_FILE_BYTES"
