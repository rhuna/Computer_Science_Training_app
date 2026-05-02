@echo off
kotlinc Main.kt -include-runtime -d main.jar || exit /b 1
java -jar main.jar | findstr /C:"PASS_V15_CROSS_LANGUAGE_API_CLIENT"
