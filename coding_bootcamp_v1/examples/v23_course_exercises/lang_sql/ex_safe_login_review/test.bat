@echo off
sqlite3 practice.db < queries.sql | findstr /C:"PASS_SAFE_LOGIN_REVIEW"
