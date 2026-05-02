@echo off
python main.py | findstr /C:"PASS_SQL_SCHEMA"
