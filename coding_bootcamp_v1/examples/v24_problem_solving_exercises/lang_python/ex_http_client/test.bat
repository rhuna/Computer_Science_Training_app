@echo off
python main.py | findstr /C:"PASS_HTTP_CLIENT"
