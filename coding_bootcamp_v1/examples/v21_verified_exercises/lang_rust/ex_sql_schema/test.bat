@echo off
cargo run | findstr /C:"PASS_SQL_SCHEMA"
